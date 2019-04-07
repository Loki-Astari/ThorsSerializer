---
layout: package
generate: false
nameSpace:  ThorsAnvil::Serialize
headers:
    base: ThorSerialize/Importer.h
    files:
        - name:
          functions:
            - return: std::istream&
              name:   operator>>
              param:  [   std::istream& stream, Importer const& data ]
              showParam: true
    notes: This was copied from package/ThorSerialize.md and made to look nice
           thus it must be manially maintained.
---
