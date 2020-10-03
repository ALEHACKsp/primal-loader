#include "../../../hpp/Vendor.hpp"
#include "../../../hpp/loader/segment/SegmentHeader.hpp"

void SegmentHeader::FillImports () {

   //Import function name in structure.
   ImportInfo imp_rtlInitializeSListHead = { "RtlInitializeSListHead" };
   //Simple fill m_offsetsMap. (Location where need patch import in segment)
   //What is ImportType can be found in SegmentHeader.hpp
   imp_rtlInitializeSListHead.m_offsetsMap.emplace (ImportType::INTERNAL, 0x0);

   //Insert name of module in map, and imports in vector.
   m_imports.emplace ("ntdll.dll", std::vector<ImportInfo> ({ imp_rtlInitializeSListHead }));

}

void SegmentHeader::FillRelocations () {
    
    //Dump relocs and place it here.
    m_relocations.emplace_back (0x0);

}