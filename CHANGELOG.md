# Changelog

All notable changes to this project will be documented in this file.

This component is part of [ThorsAnvil](https://github.com/Loki-Astari/ThorsAnvil). See the [parent changelog](https://github.com/Loki-Astari/ThorsAnvil/blob/master/CHANGELOG.md) for full release history.

The format is based on [Keep a Changelog](https://keepachangelog.com/).

## [11.0.0] - 2026-06-24

### Changed
- Support "ungetting" values during parsing
- Standardized retrieval of output size
- Tweaked `Custom_Serializer` behavior

## [10.0.0] - 2026-05-15

### Changed
- Improved unique name functionality for serialization traits
- Added missing logging function
- Removed deprecated code
- Removed retired `shared_ptr` serialization support

## [9.2.0] - 2026-04-10

### Fixed
- Validated that Yaml parser is correctly initialized
- Fixed badly allocated buffer

### Changed
- Updated build tools
- Updated logging to be consistent

## [9.0.01] - 2026-01-15

### Added
- Support for Ranges serialization
- `jsonBuilder()` function for programmatic JSON construction
- `AnyObject` type for consuming arbitrary serialized data
- Export const config support
