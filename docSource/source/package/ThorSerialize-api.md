---
layout: package
generate: false
nameSpace:  ThorsAnvil::Serialize
headers:
    base: ThorSerialize
    files:
        - name:   BinaryThor.h
          functions:
            - return: Exporter<Binary<T>, T>
              name:   binExport
              param:  [  T const& value,  bool catchExceptions = false  ]
            - return: Importer<Binary<T>, T>
              name:   binImport
              param:  [  T& value,  bool catchExceptions = false  ]
          classes: []
        - name:   JsonThor.h
          functions:
            - return: Exporter<Json, T>
              name:   jsonExport
              param:  [  T const& value,  PrinterInterface::OutputType characteristics = PrinterInterface::OutputType::Default,  bool catchExceptions = false  ]
            - return: Importer<Json, T>
              name:   jsonImport
              param:  [  T& value,  ParserInterface::ParseType parseStrictness = ParserInterface::ParseType::Weak,  bool catchExceptions = false  ]
          classes: []
        - name:   YamlThor.h
          functions:
            - return: Exporter<Yaml, T>
              name:   yamlExport
              param:  [  T const& value,  PrinterInterface::OutputType characteristics = PrinterInterface::OutputType::Default,  bool catchExceptions = false  ]
            - return: Importer<Yaml, T>
              name:   yamlImport
              param:  [  T& value,  ParserInterface::ParseType parseStrictness = ParserInterface::ParseType::Weak,  bool catchExceptions = false  ]
          classes: []
children:
    - name: binExport
      value: ThorSerialize.BinaryThor.binExport.md
    - name: binImport
      value: ThorSerialize.BinaryThor.binImport.md
    - name: jsonExport
      value: ThorSerialize.JsonThor.jsonExport.md
    - name: jsonImport
      value: ThorSerialize.JsonThor.jsonImport.md
    - name: yamlExport
      value: ThorSerialize.YamlThor.yamlExport.md
    - name: yamlImport
      value: ThorSerialize.YamlThor.yamlImport.md
---
