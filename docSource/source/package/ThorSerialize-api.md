---
layout: package
generate: false
nameSpace:  ThorsAnvil::Serialize
headers:
    base: ThorSerialize
    files:
        - name:   JsonThor.h
          functions:
            - return: Exporter<Json, T>
              name:   jsonExport
              param:  [  T const& value,  PrinterInterface::OutputType characteristics = PrinterInterface::OutputType::Default,  bool catchExceptions = false  ]
            - return: Importer<Json, T>
              name:   jsonImport
              param:  [  T& value,  ParserInterface::ParseType parseStrictness = ParserInterface::ParseType::Weak,  bool catchExceptions = false  ]
          classes: []
children:
    - name: jsonExport
      value: ThorSerialize.JsonThor.jsonExport.md
    - name: jsonImport
      value: ThorSerialize.JsonThor.jsonImport.md
---
