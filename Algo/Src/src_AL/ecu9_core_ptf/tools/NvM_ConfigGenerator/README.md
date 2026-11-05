# NvM configuration generator

This NvM-specific tool generates the AL077 NvM configuration from
`config\NvM.yaml`. It does not generate or overwrite TI MCAL Fee or MemIf
configuration.

Double-click `Regenerate_NvM.bat` to regenerate the checked-in target configuration.
It uses the Windows Python launcher, reports success or failure, and pauses so the
result remains visible. The equivalent command from the repository root is:

```powershell
py -3 tools\NvM_ConfigGenerator\generate_nvm_config.py `
  --config tools\NvM_ConfigGenerator\config\NvM.yaml `
  --output Src\config_AL\Al\Al077\bsw\NvM
```

The generator supports the upstream derived-number behavior using
`fee_block_base_number` and the AL077-specific `fee_block_numbers` extension for
non-contiguous Fee IDs. The `fee_refs` are mapped to AL077's `FEE_BLOCK_*_ID`
symbols, and `fee_block_size` values match the corresponding Fee capacities.

Install PyYAML with
`py -3 -m pip install -r tools\NvM_ConfigGenerator\requirements.txt`.
Run the tests from this directory with
`py -3 -B -m unittest -v test_generate_nvm_config.py`.
