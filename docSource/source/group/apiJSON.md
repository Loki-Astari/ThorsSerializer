---
layout: package
generate: false
nameSpace:  ThorsAnvil::Serialize
headers:
    base: ThorSerialize/JsonThor.h
    files:
        - name:
          functions:
            - return: Exporter<T, Json>
              name:   jsonExport
              param:  [   T const& value ]
              showParam: true
            - return: Importer<T, Json>
              name:   jsonImport
              param:  [   T& value ]
              showParam: true
    notes: This was copied from package/ThorSerialize.md and made to look nice
           thus it must be manially maintained.
---
