from pathlib import Path
import argparse
import sys

PROJECT_ROOT = Path(__file__).resolve().parents[1]
if str(PROJECT_ROOT) not in sys.path:
    sys.path.insert(0, str(PROJECT_ROOT))

try:
    import yaml
except ImportError as error:
    raise SystemExit(
        "Install generator dependencies with: "
        "python -m pip install -r tools\\NvM_ConfigGenerator\\requirements.txt"
    ) from error

import re
from config_generator_common import (
    boolean, c_seconds_literal, crc_type_name, integer, positive_seconds,
    reject_unknown_keys,
)


def fee_block_numbers(config):
    blocks = config["blocks"]
    dataset_selection_bits = int(any(
        block.get("management_type", "native") == "redundant" for block in blocks))
    result = {}
    for block in blocks:
        block_count = 2 if block.get("management_type", "native") == "redundant" else 1
        explicit_numbers = block.get("fee_block_numbers")
        if explicit_numbers is not None:
            result[integer(block, "id")] = explicit_numbers
        else:
            base_number = integer(block, "fee_block_base_number")
            result[integer(block, "id")] = [
                (base_number << dataset_selection_bits) + data_index
                for data_index in range(block_count)
            ]
    return result

def validate_nvm(config):
    if not isinstance(config, dict):
        raise ValueError("nvm configuration must be a mapping")
    reject_unknown_keys(config, {
        "blocks", "standard_job_queue_size", "crc_bytes_per_call", "api_config_class",
        "repeat_mirror_operations", "dev_error_detect", "driver_mode_switch",
        "dynamic_configuration", "job_prioritization",
        "bswm_multi_block_job_status_information", "bswm_interface_include",
        "compiled_config_id",
        "main_function_period_seconds", "polling_mode",
        "set_ram_block_status_api", "version_info_api", "dem_events", "vendor_id",
        "module_id", "sw_major_version", "sw_minor_version", "sw_patch_version",
        "single_block_callback", "multi_block_callback", "block_header_include",
    }, "NvM configuration")
    for key in ("vendor_id", "module_id"):
        if integer(config, key, 0) > 65535:
            raise ValueError("%s must fit in uint16" % key)
    for key in ("sw_major_version", "sw_minor_version", "sw_patch_version"):
        if integer(config, key, 0) > 255:
            raise ValueError("%s must fit in uint8" % key)
    # NVM-SWS §3.3: retain the required project configuration identity as uint16.
    if integer(config, "compiled_config_id") > 65535:
        raise ValueError("compiled_config_id must fit in uint16")
    positive_seconds(config, "main_function_period_seconds")
    blocks = config.get("blocks")
    if not isinstance(blocks, list) or not blocks:
        raise ValueError("nvm.blocks must contain at least one block")
    queue_size = integer(config, "standard_job_queue_size", 4)
    crc_bytes_per_call = integer(config, "crc_bytes_per_call", 64)
    if queue_size < 1 or queue_size > 65535:
        raise ValueError("standard_job_queue_size must be in 1..65535")
    if crc_bytes_per_call < 1 or crc_bytes_per_call > 65535:
        raise ValueError("crc_bytes_per_call must be in 1..65535")
    if integer(config, "api_config_class", 2) != 2:
        raise ValueError("api_config_class must be 2 in the current profile")
    if integer(config, "repeat_mirror_operations", 0) != 0:
        raise ValueError("repeat_mirror_operations must be 0 in the current profile")
    for key in (
        "dev_error_detect", "driver_mode_switch", "dynamic_configuration",
        "job_prioritization",
    ):
        if boolean(config, key, False):
            raise ValueError("%s must be false in the current profile" % key)
    if not boolean(config, "polling_mode", True):
        raise ValueError("polling_mode must be true in the current profile")
    bswm_interface_include = config.get("bswm_interface_include")
    if bswm_interface_include is not None and (
        not isinstance(bswm_interface_include, str) or
        re.fullmatch(r"[A-Za-z0-9_./-]+", bswm_interface_include) is None or
        any(part in ("", ".", "..") for part in bswm_interface_include.split("/"))
    ):
        raise ValueError("bswm_interface_include must be a relative header path")
    boolean(config, "set_ram_block_status_api", True)
    boolean(config, "version_info_api", True)
    for key in ("single_block_callback", "multi_block_callback"):
        callback = config.get(key)
        if (callback is not None) and (
            not isinstance(callback, str) or
            re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", callback) is None
        ):
            raise ValueError("%s must be a C identifier" % key)
    block_header_include = config.get("block_header_include", [])
    if isinstance(block_header_include, str):
        block_header_include = [block_header_include]
    if not isinstance(block_header_include, list):
        raise ValueError("block_header_include must be a header path or list of header paths")
    for include in block_header_include:
        if (not isinstance(include, str) or
            re.fullmatch(r"[A-Za-z0-9_./-]+", include) is None or
            any(part in ("", ".", "..") for part in include.split("/"))):
            raise ValueError("block_header_include entries must be relative header paths")
    dem_events = config.get("dem_events", {})
    valid_dem_events = {
        "hardware", "integrity_failed", "request_failed", "loss_of_redundancy",
        "write_protected",
    }
    if not isinstance(dem_events, dict):
        raise ValueError("dem_events must be a mapping")
    if not set(dem_events).issubset(valid_dem_events):
        raise ValueError("dem_events contains an unsupported event name")
    event_ids = set()
    for event_name, event_id in dem_events.items():
        if not isinstance(event_id, int) or isinstance(event_id, bool) or not 1 <= event_id <= 65535:
            raise ValueError("dem_events.%s must be in 1..65535" % event_name)
        if event_id in event_ids:
            raise ValueError("dem event IDs must be unique")
        event_ids.add(event_id)

    has_redundant_block = any(
        isinstance(block, dict) and block.get("management_type", "native") == "redundant"
        for block in blocks
    )
    max_block_id = (1 << (16 - int(has_redundant_block))) - 1
    ids = set()
    base_numbers = set()
    for block in blocks:
        if not isinstance(block, dict):
            raise ValueError("each nvm.blocks entry must be a mapping")
        reject_unknown_keys(block, {
            "id", "length", "fee_block_base_number", "fee_block_numbers",
            "fee_block_size", "management_type",
            "resistant_to_changed_sw", "use_sync_mechanism", "use_auto_validation",
            "write_verification", "rom_defaults", "crc", "init_callback",
            "calc_ram_block_crc", "permanent_ram", "crc_compare_mechanism",
            "use_set_ram_block_status", "select_block_for_read_all",
            "select_block_for_write_all", "bswm_block_status_information",
            "static_block_id_check", "max_read_retries",
            "max_write_retries", "write_protected", "write_once", "target_block_reference",
        }, "NvM block")
        block_id = integer(block, "id")
        length = integer(block, "length")
        fee_block_size = integer(block, "fee_block_size")
        if block_id < 2 or block_id > max_block_id:
            raise ValueError("block id must be in 2..%d" % max_block_id)
        if length < 1 or length > 65535:
            raise ValueError("block %d length must be in 1..65535" % block_id)
        if fee_block_size < 1 or fee_block_size > 65535:
            raise ValueError("block %d fee_block_size must be in 1..65535" % block_id)

        # NVM-SWS-031; test_fee_target_references_must_be_valid_and_unique resolves Fee targets.
        target_reference = block.get("target_block_reference")
        if not isinstance(target_reference, dict):
            raise ValueError("block %d target_block_reference must be a mapping" % block_id)
        reject_unknown_keys(target_reference, {"backend", "fee_refs"},
                            "block %d target_block_reference" % block_id)
        if target_reference.get("backend") != "fee":
            raise ValueError("block %d target_block_reference backend must be fee" % block_id)
        fee_refs = target_reference.get("fee_refs")
        if not isinstance(fee_refs, list) or not fee_refs:
            raise ValueError("block %d target_block_reference fee_refs must be a non-empty list" % block_id)
        if any((not isinstance(name, str) or
                re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", name) is None) for name in fee_refs):
            raise ValueError("block %d target_block_reference fee_refs must be C identifiers" % block_id)
        if len({name.upper() for name in fee_refs}) != len(fee_refs):
            raise ValueError("block %d target_block_reference fee_refs must be unique" % block_id)

        management_type = block.get("management_type", "native")
        if management_type not in ("native", "redundant"):
            raise ValueError("block %d has unsupported management_type: %s" % (block_id, management_type))

        if "resistant_to_changed_sw" not in block:
            raise ValueError("block %d must define resistant_to_changed_sw" % block_id)
        boolean(block, "resistant_to_changed_sw")
        boolean(block, "bswm_block_status_information", False)
        for key in ("use_sync_mechanism", "use_auto_validation", "write_verification"):
            if boolean(block, key, False):
                raise ValueError("block %d %s must be false in the current profile" % (block_id, key))

        if "fee_block_numbers" in block:
            numbers = block["fee_block_numbers"]
            expected_count = 2 if management_type == "redundant" else 1
            if not isinstance(numbers, list) or len(numbers) != expected_count:
                raise ValueError(
                    "block %d fee_block_numbers must contain one number per NV copy" %
                    block_id)
            if any(
                not isinstance(number, int) or isinstance(number, bool) or
                not 1 <= number <= 65534
                for number in numbers
            ):
                raise ValueError("block %d fee_block_numbers must be in 1..65534" % block_id)
        else:
            base_number = integer(block, "fee_block_base_number")
            if base_number < 1 or base_number > 65534:
                raise ValueError("block %d fee_block_base_number must be in 1..65534" % block_id)
            if base_number in base_numbers:
                raise ValueError("duplicate Fee block base number: %d" % base_number)
            base_numbers.add(base_number)

        defaults = block.get("rom_defaults")
        if defaults is not None and not isinstance(defaults, list):
            raise ValueError("block %d rom_defaults must be a list" % block_id)
        crc = block.get("crc", {})
        if not isinstance(crc, dict):
            raise ValueError("block %d crc must be a mapping" % block_id)
        reject_unknown_keys(crc, {"enabled", "type"}, "block %d crc" % block_id)
        init_callback = block.get("init_callback")
        if (init_callback is not None) and (
            not isinstance(init_callback, str) or
            re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", init_callback) is None
        ):
            raise ValueError("block %d init_callback must be a C identifier" % block_id)
        crc_type = crc_type_name(crc)
        if block_id in ids:
            raise ValueError("duplicate NvM block id: %d" % block_id)
        if defaults is not None and len(defaults) != length:
            raise ValueError("block %d length and rom_defaults do not match" % block_id)
        if defaults is not None and any(
            not isinstance(value, int) or isinstance(value, bool) or not 0 <= value <= 255
            for value in defaults
        ):
            raise ValueError("block %d rom_defaults must contain uint8 values" % block_id)
        if crc_type not in ("none", "crc8", "crc16", "crc32"):
            raise ValueError("block %d has unsupported CRC type: %s" % (block_id, crc_type))
        crc_enabled = boolean(crc, "enabled", False)
        if crc_enabled and crc_type == "none":
            raise ValueError("block %d enables CRC but has type none" % block_id)
        if not crc_enabled and crc_type != "none":
            raise ValueError("block %d configures CRC type while CRC is disabled" % block_id)
        crc_size = {"none": 0, "crc8": 1, "crc16": 2, "crc32": 4}[crc_type]
        if fee_block_size < length + (crc_size if crc_enabled else 0):
            raise ValueError("block %d fee_block_size must cover NvM data and CRC" % block_id)
        if boolean(block, "calc_ram_block_crc", False) and not crc_enabled:
            raise ValueError("block %d calc_ram_block_crc requires CRC" % block_id)
        permanent_ram = boolean(block, "permanent_ram", True)
        if boolean(block, "calc_ram_block_crc", False) and not permanent_ram:
            raise ValueError("block %d calc_ram_block_crc requires permanent RAM" % block_id)
        # NVM-SWS-016: callback restore needs a configured RAM target without ROM defaults.
        if (init_callback is not None) and not permanent_ram and defaults is None:
            raise ValueError("block %d init_callback without ROM defaults requires permanent RAM" % block_id)
        if boolean(block, "crc_compare_mechanism", False) and not crc_enabled:
            raise ValueError("block %d crc_compare_mechanism requires CRC" % block_id)
        if boolean(block, "use_set_ram_block_status", False) and not boolean(
            config, "set_ram_block_status_api", True
        ):
            raise ValueError("block %d use_set_ram_block_status requires the API" % block_id)
        if boolean(block, "use_set_ram_block_status", False) and not permanent_ram:
            raise ValueError("block %d use_set_ram_block_status requires permanent RAM" % block_id)
        boolean(block, "select_block_for_read_all", True)
        boolean(block, "select_block_for_write_all", True)
        if boolean(block, "static_block_id_check", False):
            raise ValueError("static_block_id_check is not enabled in the current profile")
        integer(block, "max_read_retries", 0)
        integer(block, "max_write_retries", 0)
        if integer(block, "max_read_retries", 0) > 7 or integer(block, "max_write_retries", 0) > 7:
            raise ValueError("block %d retry counts must be in 0..7" % block_id)
        boolean(block, "write_protected", False)
        boolean(block, "write_once", False)
        ids.add(block_id)

    bswm_block_status_enabled = any(
        boolean(block, "bswm_block_status_information", False) for block in blocks
    )
    bswm_notifications_enabled = boolean(
        config, "bswm_multi_block_job_status_information", True
    ) or bswm_block_status_enabled
    if bswm_notifications_enabled and bswm_interface_include is None:
        raise ValueError(
            "bswm_interface_include is required when BswM status notifications are enabled"
        )

    fee_numbers = fee_block_numbers(config)
    seen_fee_numbers = set()
    for block_id, block_numbers in fee_numbers.items():
        for block_number in block_numbers:
            if block_number < 1 or block_number > 65534:
                raise ValueError("derived Fee block number must be in 1..65534")
            if block_number in seen_fee_numbers:
                raise ValueError("duplicate Fee block number: %d" % block_number)
            seen_fee_numbers.add(block_number)
    for block in blocks:
        block_id = integer(block, "id")
        if len(block["target_block_reference"]["fee_refs"]) != len(fee_numbers[block_id]):
            raise ValueError("block %d must reference one Fee block per NV copy" % block_id)


def generate_nvm(config, output):
    blocks = config["blocks"]
    output.mkdir(parents=True, exist_ok=True)
    bswm_block_status_enabled = any(
        boolean(block, "bswm_block_status_information", False) for block in blocks
    )
    header = [
        "#ifndef NVM_CFG_H", "#define NVM_CFG_H", '', '#include "NvM_Types.h"', '',
        "#define NVM_CFG_BLOCK_COUNT %dU /* Number of configured NvM block descriptors. */" %
        len(blocks),
        "#define NVM_CFG_COMPILED_CONFIG_ID %dU /* Compiled configuration identity; NVM-SWS §3.3. */" %
        integer(config, "compiled_config_id"),
        "#define NVM_CFG_MAIN_FUNCTION_PERIOD_SECONDS %s /* NVMCommon NvMMainFunctionPeriod, in seconds. */" %
        c_seconds_literal(positive_seconds(config, "main_function_period_seconds")),
        "#define NVM_CFG_STANDARD_JOB_QUEUE_SIZE %dU /* Maximum number of standard asynchronous jobs that can wait in the NvM queue. */" %
        integer(config, "standard_job_queue_size", 4),
        "#define NVM_CFG_CRC_BYTES_PER_CALL %dU /* Maximum incremental CRC data bytes per main-function call. */" %
        integer(config, "crc_bytes_per_call", 64),
        "#define NVM_CFG_SET_RAM_BLOCK_STATUS_API %dU /* Enable NvM_SetRamBlockStatus in the API profile. */" %
        (1 if boolean(config, "set_ram_block_status_api", True) else 0),
        "#define NVM_CFG_VERSION_INFO_API %dU /* Enable NvM_GetVersionInfo in the API profile. */" %
        (1 if boolean(config, "version_info_api", True) else 0),
        "#define NVM_CFG_VENDOR_ID %dU /* AUTOSAR vendor identifier reported by NvM. */" %
        integer(config, "vendor_id", 0),
        "#define NVM_CFG_MODULE_ID %dU /* AUTOSAR module identifier assigned to NvM. */" %
        integer(config, "module_id", 20),
        "#define NVM_CFG_SW_MAJOR_VERSION %dU /* Major software version returned by NvM. */" %
        integer(config, "sw_major_version", 0),
        "#define NVM_CFG_SW_MINOR_VERSION %dU /* Minor software version returned by NvM. */" %
        integer(config, "sw_minor_version", 0),
        "#define NVM_CFG_SW_PATCH_VERSION %dU /* Patch software version returned by NvM. */" %
        integer(config, "sw_patch_version", 0),
        "#define NVM_CFG_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION %dU /* Enable global multi-block BswM status notifications. */" %
        (1 if boolean(config, "bswm_multi_block_job_status_information", True) else 0),
        "#define NVM_CFG_BSWM_BLOCK_STATUS_INFORMATION %dU /* At least one block enables BswM block status notifications. */" %
        (1 if bswm_block_status_enabled else 0),
    ]
    bswm_interface_include = config.get("bswm_interface_include")
    if bswm_interface_include is not None and (
        boolean(config, "bswm_multi_block_job_status_information", True) or
        bswm_block_status_enabled
    ):
        header.append(
            '#define NVM_CFG_BSWM_INTERFACE_INCLUDE "%s" /* BswM NvM notification interface header. */' %
            bswm_interface_include
        )
    block_header_includes = config.get("block_header_include", [])
    if isinstance(block_header_includes, str):
        block_header_includes = [block_header_includes]
    header[4:4] = ['#include "%s"' % include for include in block_header_includes]
    single_block_callback = config.get("single_block_callback")
    multi_block_callback = config.get("multi_block_callback")
    header.extend([
        "#define NVM_CFG_SINGLE_BLOCK_CALLBACK_ENABLED %dU /* Single-block completion callback configured. */" %
        (1 if single_block_callback is not None else 0),
        "#define NVM_CFG_MULTI_BLOCK_CALLBACK_ENABLED %dU /* Multi-block completion callback configured. */" %
        (1 if multi_block_callback is not None else 0),
    ])
    if single_block_callback is not None:
        header.extend([
            "#define NVM_CFG_SINGLE_BLOCK_CALLBACK %s /* Single-block job completion callback. */" %
            single_block_callback,
            "Std_ReturnType %s(NvM_BlockRequestType BlockRequest, "
            "NvM_RequestResultType JobResult); /* Configured single-block callback interface. */" %
            single_block_callback,
        ])
    if multi_block_callback is not None:
        header.extend([
            "#define NVM_CFG_MULTI_BLOCK_CALLBACK %s /* Multi-block job completion callback. */" %
            multi_block_callback,
            "Std_ReturnType %s(NvM_MultiBlockRequestType MultiBlockRequest, "
            "NvM_RequestResultType JobResult); /* Configured multi-block callback interface. */" %
            multi_block_callback,
        ])
    dem_events = config.get("dem_events", {})
    dem_event_macros = {
        "hardware": "HARDWARE",
        "integrity_failed": "INTEGRITY_FAILED",
        "request_failed": "REQUEST_FAILED",
        "loss_of_redundancy": "LOSS_OF_REDUNDANCY",
        "write_protected": "WRITE_PROTECTED",
    }
    header.append("#define NVM_CFG_DEM_ENABLED %dU /* Any DEM event IDs are configured. */" %
                  (1 if dem_events else 0))
    dem_event_descriptions = {
        "hardware": "hardware or lower-layer failure",
        "integrity_failed": "stored block integrity validation failure",
        "request_failed": "NvM request failure",
        "loss_of_redundancy": "loss of one valid redundant storage copy",
        "write_protected": "write request rejected because the block is protected",
    }
    for event_name, macro_name in dem_event_macros.items():
        event_id = dem_events.get(event_name, 0)
        header.append("#define NVM_CFG_DEM_EVENT_%s_ENABLED %dU /* Event enabled for %s. */" % (
            macro_name, 1 if event_id != 0 else 0, dem_event_descriptions[event_name]))
        header.append("#define NVM_CFG_DEM_EVENT_%s_ID %dU /* DEM identifier for %s. */" % (
            macro_name, event_id, dem_event_descriptions[event_name]))
    max_physical_length = max(
        integer(block, "fee_block_size")
        for block in blocks
    )
    header.append("#define NVM_CFG_MAX_PHYSICAL_BLOCK_LENGTH %dU /* Largest referenced physical Fee payload, in bytes. */" %
                  max_physical_length)
    header.extend([
        '',
        "typedef struct",
        "{",
        "    NvM_BlockIdType block_id;",
        "    uint16 block_length;",
        "    uint8 memif_device_index;",
        "    uint16 memif_block_number;",
        "    uint16 memif_redundant_block_number;",
        "    uint8 nv_block_count;",
        "    uint16 fee_block_size;",
        "    NvM_BlockManagementType management_type;",
        "    uint8 *ram_ptr;",
        "    const uint8 *rom_ptr;",
        "    NvM_InitBlockCallbackType init_block_callback;",
        "    boolean write_protected;",
        "    boolean write_once;",
        "    boolean resistant_to_changed_sw;",
        "    uint8 max_read_retries;",
        "    uint8 max_write_retries;",
        "    boolean crc_enabled;",
        "    NvM_CrcType crc_type;",
        "    boolean crc_compare_mechanism;",
        "    boolean calc_ram_block_crc;",
        "    boolean use_set_ram_block_status;",
        "    boolean select_block_for_read_all;",
        "    boolean select_block_for_write_all;",
        "    boolean bswm_block_status_information;",
        "} NvM_BlockDescriptorType;",
        "typedef NvM_BlockDescriptorType NvM_BlockConfigType;",
        '',
    ])
    source = ['#include "Fee_Cfg.h"', '#include "NvM_Cfg.h"', '']
    block_lines = []
    block_parameter_descriptions = {
        "id": "NvM block identifier.",
        "length": "Number of data bytes in this block.",
        "fee_block_base_number": "Base Fee block number used to derive the physical logical block binding.",
        "management_type": "Native stores one copy; redundant management stores two copies.",
        "resistant_to_changed_sw": "Preserve the block's data when the application software version changes.",
        "write_protected": "Reject write requests for this block when enabled.",
        "write_once": "Permit at most one successful write after initialization when enabled.",
        "use_set_ram_block_status": "Allow this block to use NvM_SetRamBlockStatus when the API is enabled.",
        "select_block_for_read_all": "Include this block in NvM_ReadAll when its selection state permits.",
        "select_block_for_write_all": "Include this block in NvM_WriteAll when its selection state permits.",
        "max_read_retries": "Additional lower-layer read attempts after an unsuccessful read.",
        "max_write_retries": "Additional lower-layer write attempts after an unsuccessful write.",
        "crc_compare_mechanism": "Compare the calculated RAM CRC with the stored CRC to detect changes.",
        "calc_ram_block_crc": "Calculate and maintain the CRC for the RAM copy.",
    }
    crc_enums = {"none": "NVM_CRC_NONE", "crc8": "NVM_CRC8", "crc16": "NVM_CRC16", "crc32": "NVM_CRC32"}
    for block in blocks:
        block_id = integer(block, "id")
        length = integer(block, "length")
        crc = block.get("crc", {})
        crc_type = crc_type_name(crc)
        header.extend([
            "#define NVM_CFG_BLOCK_%d_LENGTH %dU /* NvM block %d data length in bytes. */" %
            (block_id, length, block_id),
        ])
        permanent_ram = boolean(block, "permanent_ram", True)
        if permanent_ram:
            header.append(
                "extern uint8 NvM_CfgRamBlock_%d[NVM_CFG_BLOCK_%d_LENGTH]; "
                "/* Permanent RAM data for NvM block %d. */" %
                (block_id, block_id, block_id))
        if block.get("rom_defaults") is not None:
            header.append(
                "extern const uint8 NvM_CfgRomDefaults_%d[NVM_CFG_BLOCK_%d_LENGTH]; "
                "/* ROM defaults for NvM block %d. */" %
                (block_id, block_id, block_id))
        if block.get("init_callback") is not None:
            header.append("Std_ReturnType %s(NvM_InitBlockRequestType InitBlockRequest);" %
                          block["init_callback"])
        defaults = block.get("rom_defaults")
        defaults_ptr = "NvM_CfgRomDefaults_%d" % block_id if defaults is not None else "NULL_PTR"
        callback_ptr = block.get("init_callback", "NULL_PTR")
        defaults_definition = []
        if defaults is not None:
            defaults = ", ".join("%dU" % value for value in defaults)
            defaults_definition = [
                "#define NVM_START_SEC_CONST_8",
                '#include "NvM_MemMap.h"',
                "const uint8 NvM_CfgRomDefaults_%d[NVM_CFG_BLOCK_%d_LENGTH] = { %s }; "
                "/* ROM default data for NvM block %d. */" %
                (block_id, block_id, defaults, block_id),
                "#define NVM_STOP_SEC_CONST_8",
                '#include "NvM_MemMap.h"', '']
        ram_ptr = "NvM_CfgRamBlock_%d" % block_id if permanent_ram else "NULL_PTR"
        if permanent_ram:
            source.extend([
                "#define NVM_START_SEC_VAR_CLEARED_8",
                '#include "NvM_MemMap.h"',
                "uint8 NvM_CfgRamBlock_%d[NVM_CFG_BLOCK_%d_LENGTH]; "
                "/* Permanent RAM data for NvM block %d. */" %
                (block_id, block_id, block_id),
                "#define NVM_STOP_SEC_VAR_CLEARED_8",
                '#include "NvM_MemMap.h"',
            ])
        source.extend(defaults_definition)
        fee_references = block["target_block_reference"]["fee_refs"]
        fee_number_0 = fee_references[0]
        fee_number_1 = (fee_references[1]
                if len(fee_references) > 1 else "0U")
        fee_size = "%dU" % integer(block, "fee_block_size")
        management_type = block.get("management_type", "native")
        descriptor_values = [
            ("%dU" % block_id, "NvM block identifier."),
            ("%dU" % length, "Number of data bytes in this block."),
            ("0U", "MemIf device index; this profile uses device 0."),
            (fee_number_0, "Primary Fee block reference: %s; NvMTargetBlockReference/NvMFeeRef." %
             fee_references[0]),
            (fee_number_1, "Redundant Fee block reference: %s; NvMTargetBlockReference/NvMFeeRef." %
             (fee_references[1] if len(fee_references) > 1 else "not used")),
            ("%dU" % len(fee_references), "Number of configured Fee copies."),
            (fee_size, "Fee payload capacity in bytes."),
            ("NVM_BLOCK_%s" % management_type.upper(),
             "%s management." % management_type.capitalize()),
            (ram_ptr, "Permanent RAM data pointer." if permanent_ram else
             "No permanent RAM pointer; caller supplies RAM."),
            (defaults_ptr, "ROM defaults pointer." if defaults is not None else
             "No ROM defaults configured."),
            (callback_ptr, "Initialization callback configured for this block." if
             callback_ptr != "NULL_PTR" else "No initialization callback configured."),
            ("TRUE" if boolean(block, "write_protected", False) else "FALSE",
             "Write protection enabled." if boolean(block, "write_protected", False) else
             "Write protection disabled."),
            ("TRUE" if boolean(block, "write_once", False) else "FALSE",
             "Write-once behavior enabled." if boolean(block, "write_once", False) else
             "Write-once behavior disabled."),
            ("TRUE" if boolean(block, "resistant_to_changed_sw") else "FALSE",
             "Data is retained across software changes." if
             boolean(block, "resistant_to_changed_sw") else
             "Data is not retained across software changes."),
            ("%dU" % integer(block, "max_read_retries", 0),
             "Additional retries after failed reads."),
            ("%dU" % integer(block, "max_write_retries", 0),
             "Additional retries after failed writes."),
            ("TRUE" if boolean(crc, "enabled", False) else "FALSE",
             "CRC protection enabled." if boolean(crc, "enabled", False) else
             "CRC protection disabled."),
            (crc_enums[crc_type], "Configured CRC algorithm: %s." % crc_type),
            ("TRUE" if boolean(block, "crc_compare_mechanism", False) else "FALSE",
             "Compare RAM CRC with stored CRC." if
             boolean(block, "crc_compare_mechanism", False) else
             "Do not compare RAM CRC with stored CRC."),
            ("TRUE" if boolean(block, "calc_ram_block_crc", False) else "FALSE",
             "Maintain CRC for the RAM copy." if
             boolean(block, "calc_ram_block_crc", False) else
             "Do not maintain CRC for the RAM copy."),
            ("TRUE" if boolean(block, "use_set_ram_block_status", False) else "FALSE",
             "Allow NvM_SetRamBlockStatus for this block." if
             boolean(block, "use_set_ram_block_status", False) else
             "Do not allow NvM_SetRamBlockStatus for this block."),
            ("TRUE" if boolean(block, "select_block_for_read_all", True) else "FALSE",
             "Selected for NvM_ReadAll." if
             boolean(block, "select_block_for_read_all", True) else
             "Not selected for NvM_ReadAll."),
            ("TRUE" if boolean(block, "select_block_for_write_all", True) else "FALSE",
             "Selected for NvM_WriteAll." if
             boolean(block, "select_block_for_write_all", True) else
             "Not selected for NvM_WriteAll."),
            ("TRUE" if boolean(block, "bswm_block_status_information", False) else "FALSE",
             "Report block status to BswM." if
             boolean(block, "bswm_block_status_information", False) else
             "Do not report block status to BswM."),
        ]
        descriptor_lines = [
            "        %s%s /* %s */" % (
                value, "," if index < len(descriptor_values) - 1 else "", description)
            for index, (value, description) in enumerate(descriptor_values)
        ]
        block_lines.append("    {\n%s\n    }" % "\n".join(descriptor_lines))
    header.extend(['', 'extern const NvM_BlockDescriptorType NvM_BlockDescriptorTable[NVM_CFG_BLOCK_COUNT];',
                   '', '#endif /* NVM_CFG_H */', ''])
    source.extend([
        "#define NVM_START_SEC_CONST_UNSPECIFIED",
        '#include "NvM_MemMap.h"',
        'const NvM_BlockDescriptorType NvM_BlockDescriptorTable[NVM_CFG_BLOCK_COUNT] =',
        '{', ',\n'.join(block_lines), '};',
        "#define NVM_STOP_SEC_CONST_UNSPECIFIED",
        '#include "NvM_MemMap.h"', '',
    ])
    (output / "NvM_Cfg.h").write_text("\n".join(header), encoding="utf-8")
    (output / "NvM_Cfg.c").write_text("\n".join(source), encoding="utf-8")

def main():
    parser = argparse.ArgumentParser(description="Generate NvM configuration from one YAML file.")
    parser.add_argument("--config", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    try:
        config = yaml.safe_load(args.config.read_text(encoding="utf-8"))
        validate_nvm(config)
        generate_nvm(config, args.output)
    except (OSError, ValueError, yaml.YAMLError) as error:
        print("NvM configuration generation failed: %s" % error, file=sys.stderr)
        return 1
    print("generated NvM configuration in %s" % args.output)
    return 0


if __name__ == "__main__":
    sys.exit(main())
