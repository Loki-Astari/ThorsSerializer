---
layout: package
generate: false
nameSpace:  ThorsAnvil::Serialize
headers:
    base: ThorSerialize/YamlThor.h
    files:
        - name:
          functions:
            - return: Exporter<T, Yaml>
              name:   yamlExport
              param:  [   T const& value ]
              showParam: true
            - return: Importer<T, Yaml>
              name:   yamlImport
              param:  [   T& value ]
              showParam: true
    notes: This was copied from package/ThorSerialize.md and made to look nice
           thus it must be manially maintained.
---
