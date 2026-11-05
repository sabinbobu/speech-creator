import copy
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

import yaml

from generate_nvm_config import fee_block_numbers, generate_nvm, validate_nvm


TOOL_ROOT = Path(__file__).resolve().parent
PROJECT_ROOT = TOOL_ROOT.parent.parent
CONFIG_PATH = TOOL_ROOT / "config" / "NvM.yaml"
TARGET_PATH = PROJECT_ROOT / "Src" / "config_AL" / "Al" / "Al077" / "bsw" / "NvM"


def load_config():
    return yaml.safe_load(CONFIG_PATH.read_text(encoding="utf-8"))


class GenerateNvMConfigTests(unittest.TestCase):
    def test_al077_configuration_validates_and_maps_fee_ids(self):
        config = load_config()
        validate_nvm(config)

        self.assertEqual(fee_block_numbers(config), {
            2: [16],
            3: [17, 33],
            4: [32],
            5: [48],
            6: [65],
            7: [80],
            8: [64, 81],
        })

    def test_generated_files_match_checked_in_al077_configuration(self):
        config = load_config()
        validate_nvm(config)

        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory)
            generate_nvm(config, output)

            for filename in ("NvM_Cfg.c", "NvM_Cfg.h"):
                self.assertEqual(
                    (TARGET_PATH / filename).read_text(encoding="utf-8"),
                    (output / filename).read_text(encoding="utf-8"),
                    filename,
                )

    def test_generated_descriptors_use_al077_fee_symbols(self):
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory)
            generate_nvm(load_config(), output)
            source = (output / "NvM_Cfg.c").read_text(encoding="utf-8")
            header = (output / "NvM_Cfg.h").read_text(encoding="utf-8")
            filenames = {path.name for path in output.iterdir()}

        for fee_macro in (
            "FEE_BLOCK_16_ID", "FEE_BLOCK_17_ID", "FEE_BLOCK_33_ID",
            "FEE_BLOCK_32_ID", "FEE_BLOCK_48_ID", "FEE_BLOCK_65_ID",
            "FEE_BLOCK_80_ID", "FEE_BLOCK_64_ID", "FEE_BLOCK_81_ID",
        ):
            self.assertIn(fee_macro, source)
        self.assertIn("#define NVM_CFG_DEM_ENABLED 0U", header)
        self.assertIn("#define NVM_CFG_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION 0U", header)
        self.assertIn("#define NVM_CFG_BSWM_BLOCK_STATUS_INFORMATION 0U", header)
        self.assertNotIn("NvM_TestInitCallback", source)
        self.assertEqual(filenames, {"NvM_Cfg.c", "NvM_Cfg.h"})

    def test_bswm_notifications_require_and_emit_interface(self):
        config = copy.deepcopy(load_config())
        config["bswm_multi_block_job_status_information"] = True
        config["bswm_interface_include"] = "BswM_NvM.h"
        config["blocks"][0]["bswm_block_status_information"] = True
        validate_nvm(config)

        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory)
            generate_nvm(config, output)
            source = (output / "NvM_Cfg.c").read_text(encoding="utf-8")
            header = (output / "NvM_Cfg.h").read_text(encoding="utf-8")

        self.assertIn('#define NVM_CFG_BSWM_INTERFACE_INCLUDE "BswM_NvM.h"', header)
        self.assertIn("TRUE /* Report block status to BswM. */", source)
        config.pop("bswm_interface_include")
        with self.assertRaisesRegex(ValueError, "bswm_interface_include is required"):
            validate_nvm(config)

    def test_duplicate_explicit_fee_numbers_are_rejected(self):
        config = copy.deepcopy(load_config())
        config["blocks"][1]["fee_block_numbers"] = [16, 33]

        with self.assertRaisesRegex(ValueError, "duplicate Fee block number"):
            validate_nvm(config)

    def test_fee_number_count_must_match_block_management(self):
        config = copy.deepcopy(load_config())
        config["blocks"][1]["fee_block_numbers"] = [17]

        with self.assertRaisesRegex(ValueError, "one number per NV copy"):
            validate_nvm(config)

    def test_fee_capacity_must_include_data_and_crc(self):
        config = copy.deepcopy(load_config())
        config["blocks"][0]["fee_block_size"] = 9

        with self.assertRaisesRegex(ValueError, "must cover NvM data and CRC"):
            validate_nvm(config)

    def test_command_line_generates_only_nvm_files(self):
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory)
            result = subprocess.run(
                [
                    sys.executable,
                    str(TOOL_ROOT / "generate_nvm_config.py"),
                    "--config",
                    str(CONFIG_PATH),
                    "--output",
                    str(output),
                ],
                cwd=TOOL_ROOT,
                capture_output=True,
                text=True,
                check=False,
            )

            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertTrue((output / "NvM_Cfg.c").is_file())
            self.assertTrue((output / "NvM_Cfg.h").is_file())
            self.assertEqual(
                {path.name for path in output.iterdir()},
                {"NvM_Cfg.c", "NvM_Cfg.h"},
            )


if __name__ == "__main__":
    unittest.main()
