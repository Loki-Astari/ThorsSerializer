---
layout: package
generate: false
nameSpace:  ThorsAnvil::Serialize
headers:
    base: ThorSerialize/BinaryThor.h
    files:
        - name:
          functions:
            - return: Exporter<T, Binary>
              name:   binaryExport
              param:  [   T const& value ]
              showParam: true
            - return: Importer<T, Binary>
              name:   binaryImport
              param:  [   T& value ]
              showParam: true
    notes: This was copied from package/ThorSerialize.md and made to look nice
           thus it must be manially maintained.
---
