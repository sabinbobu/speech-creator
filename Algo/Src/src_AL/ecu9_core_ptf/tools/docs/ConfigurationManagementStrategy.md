# Configuration Management Strategy

## 1. Purpose

This document defines the configuration management strategy for the ECU9 platform. It is intended as the reference basis for the topic and therefore describes the platform requirements, structure, and configuration model as a standalone requirement baseline.

The strategy applies to the ECU9 platform and its reusable architecture, with the objective of keeping a stable platform core while allowing ECU-specific or customer-specific variation through configuration rather than uncontrolled source-code divergence.

## 2. Strategy objectives

The platform strategy establishes the rules for requirements, software architecture, software components, and validation assets. The objective is to make the platform scalable and reusable while supporting cost reduction.

The applicable strategic goals are:

- harmonization of the development process across system development, software development, and software validation
- harmonization of the toolchain across system development, software development, and software validation
- transition from a single-project development model to a platform-driven development model
- simplification and efficiency improvements in the development process
- continuous cost-reduction objectives
- lean validation through reduced complexity, standardized toolchains, and higher reuse of validation assets

## 3. Architectural principles

The platform architecture shall:

- consider functional safety design measures in relation to code complexity, third-party software, and system constraints
- support functionalities classified as ASIL QM, ASIL A, and ASIL B
- target small-scale MCU solutions in the LEAN architecture for HL and RL ECUs
- target MCUs capable of supporting full AUTOSAR BSW and EVITA Medium cybersecurity requirements in the PRO architecture
- maintain a reusable software catalogue of components and algorithms applicable to all application projects
- keep software components modular, scalable, and parametrized
- support product evolution and the management of architectural variants
- maintain bidirectional traceability between requirements, architecture, components, and tests

## 4. Platform and component model

### 4.1 Reusable software components

The software platform shall maintain a catalogue of reusable software components and algorithms. These shall be designed so that they are:

- scalable and upgradeable over time
- reusable across application projects
- modular and parameterized
- organized into common and customer-specific parts
- capable of being downsized or upgraded between PRO and LEAN solutions where technically feasible

When full scalability is not feasible, the limitation shall be explicitly documented and handled by configuration or controlled adaptation.

### 4.2 Component structure

Software components may contain multiple software modules. The architecture shall ensure that:

- the common part is fixed and reusable
- the parameterized part supports customer-specific customization
- software components and modules conform to standard AUTOSAR interfaces where relevant
- parametrization is used instead of source duplication

## 5. Architecture and process requirements

The software architecture shall define the characteristics and design rules required to ensure compliance with the platform requirements. These rules shall include:

- the definition of architectural layers, interfaces, and permitted dependencies
- rules for modularity, reusability, and scalability
- rules for integration, configurability, and parametrization of software components
- criteria for functional safety, cybersecurity, and complexity management
- alignment with relevant standards, including AUTOSAR, ISO 26262, cybersecurity, and internal process requirements
- traceability from requirements to architecture, components, and tests
- support for product evolution and architectural variants

The architecture shall be documented and maintained so that it supports verification, validation, and consistent implementation of the platform requirements.

## 6. Configuration management model

### 6.1 Platform-owned versus project-owned content

The platform shall distinguish between:

- platform-owned artifacts, which are stable and common across ECU variants
- project-specific configuration artifacts, which define the ECU-specific variant data
- generated artifacts, which are produced from the project configuration and must be reproducible
- project-specific source artifacts, which are kept minimal and not used as the primary location for database or communication variability

The objective is to keep the platform stable while moving variability into configuration and generated data.

### 6.2 Configuration-driven variation

Configuration shall be the primary mechanism for ECU-specific adaptation. The platform shall avoid runtime mutation of routes, signals, or static communication definitions. The platform shall rely on validated, static configuration data rather than project-specific modifications to the common source code.

This principle is required to maintain reuse, deterministic behavior, and traceability across ECU variants and platforms.

## 7. Repository and build structure

The build structure shall follow a modular repository architecture. The project shall be organized such that the root project repository acts as the integration point for reusable platform content and ECU-specific configuration.

### 7.1 Project structure model

The project repository shall contain a common structure with the following conceptual areas:

- `src`
- `build`
- `CI`
- `tools`
- `config_<OEM_project>`
- `src_<OEM_project>`
- `ecu9_core_ptf`
- `cdd`
- `app`
- `rte`
- `mcal`
- `bsw`

The project identity shall remain explicit in the folder naming scheme, for example using an OEM code and project code such as:

- `AL` as the customer identifier
- `AL077` as the project identifier

This naming scheme ensures that the repository structure reflects both the platform baseline and the project-specific configuration identity.

### 7.2 Submodule-based architecture

The platform shall use a submodule-based repository strategy. The architecture explicitly supports:

- a reusable core platform module
- submodules for software components and CDDs
- standalone buildability of submodules with default configurations
- hierarchical project-level integration from the main project repository

The build architecture shall permit the following patterns:

- submodule alone: built with default configuration
- project build: built with the project-level configuration from the project root

### 7.3 Standalone platform build support

The platform structure shall support a standalone build mode with default configuration. This allows the platform to be validated and built independently of a specific project, while still following the same architecture and folder composition as the full ECU project.

The standalone build model shall include examples such as:

- uC startup / UT-Windows HAL abstraction
- empty or CDD example modules
- service layers such as EcuM, IoHwAbs, and OS wrappers where applicable
- default app examples such as a blinky application
- default RTE example
- sample MCAL configuration
- sample service-layer configuration
- empty or default CDD sample configuration

This supports both validation and integration without forcing a project-specific build to be the only validation path.

## 8. Configuration rules

### 8.1 Default configuration and project configuration

The project shall define two configuration layers:

1. default configuration for standalone module or submodule builds
2. project configuration for the complete project integration build

The rules are:

- a submodule or component built alone shall use its default or provided configuration
- a full project build shall use the project root configuration
- project-level configuration shall override or select the correct variant for the integration build

### 8.2 Configuration ownership

Configuration shall be owned and managed according to responsibility boundaries:

- the platform owns stable baseline definitions and reusable configuration templates
- the project owns the ECU-specific configuration selection and project-level tuning
- generated artifacts are owned by the build process and remain traceable to the source configuration

## 9. Platform build and validation model

The platform build model shall ensure that:

- default configurations are available for standalone component validation
- project configurations are available for full ECU integration
- configuration differences are explicit and traceable
- integration or validation failures are localized to configuration problems rather than hidden source modifications

The platform shall support a lean validation approach based on reuse of validation assets and a common toolchain. The build and validation model shall be aligned with the platform-level requirement to reduce complexity and improve efficiency.

## 10. Safety, cybersecurity, and quality requirements

The platform strategy requires the architecture to account for:

- functional safety design measures
- cybersecurity constraints for PRO platform solutions
- complexity management
- standard interface and architecture alignment
- traceability across design and validation activities

Configuration management shall therefore include the ability to preserve safety and cybersecurity-relevant metadata, route boundaries, and implementation constraints as part of the configuration and validation baseline.

## 11. Traceability and reuse model

The ECU9 platform shall maintain a clear traceability chain between:

- platform requirements
- architecture definitions
- software components and modules
- configuration data
- generated artifacts
- validation activities and test results

This traceability is required to ensure that project-specific configuration remains aligned with the reusable platform and does not silently diverge from the common architecture.

## 12. Summary

The configuration management strategy for the ECU9 platform is based on a platform-driven development model in which:

- reusable platform components remain stable and common
- project-specific variation is handled through configuration and generated artifacts
- submodules are buildable standalone and integrable into the project hierarchy
- project-root configuration is used for final integration builds
- default configuration is used for component-level standalone validation
- requirements, architecture, configuration, and validation remain traceable across the lifecycle

The core pattern is therefore:

- common platform behavior in the platform layer
- ECU-specific behavior in the configuration layer
- reproducible artifacts generated from validated configuration
- a modular build tree supporting both platform-wide reuse and project-specific adaptation
