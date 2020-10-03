#### ```[C++/x86] | Primal-loader```
___

#### Showcase:

![Configuration](https://i.imgur.com/qX7egWI.png)

####
##### How to use:
 
  ##
  ##### Stage 0: Preare segment.
  ###
  
  1. Take your dump and copy it as "C byte array". (You can use HxD for this)
  2. Move the copied array to Segment.cpp.
  3. Fix any errors with connecting the array.
  
  ##
  ##### Stage 1: Setup segment data.
  ###

  1. Fill the SegmentHeader::FillImports function with the import table.
     Example:
     ```cpp
       // Import function name in structure.
       ImportInfo imp_rtlInitializeSListHead = {"RtlInitializeSListHead"};
       // Simple fill m_offsetsMap. (Location where need patch import in segment)
       // What is ImportType can be found in SegmentHeader.hpp
       imp_rtlInitializeSListHead.m_offsetsMap.emplace (ImportType::INTERNAL, 0x0);
     ```
     Hint: IAT can be restored with Scylla. If this is not possible, then you can use your own table and iterate over each import.
     
  2. Fill the SegmentHeader::FillRelocations function with the relocations.
    Example: 
     ```cpp
         //Dump relocs and place it here.
         m_relocations.emplace_back (0x0);
     ```
     Hint: It is almost impossible to automatically restore erased relocations. But it is quite possible to dump a segment with a different address value (Largest address -> Smallest). Thus, you can go through the cycle and restore some of the relocs, but you cannot restore all relocationsd without human intervention.
  
   ##
   ##### Stage 2: Setup RuntimeHandler configuration.
   ###
   
   1. You need to set a pair of values. (In Bootstrap.cpp)
    1.0. NAD - New allocation address. (Can be 0x0 by default)
    1.1. ОАD - Old allocation address. (Base dump address)
    1.2. SGZ - Segment size. (Used for memcpy / Dump size)
    1.3. ALZ - Allocation size. (The size of the allocated memory for the segment. Should not be less than sgz!)
    1.4. OEP - Original entry point. (Offset to original dump entry point / CRT_DllMain)
  
  2. Compile & inject.

  ##
  ##### Stage 3 (Additional): Add segment framework.     
  ###
  
   1. You can set the actions that the loader should perform before and after OEP in SegmentInterpreter.
Hint: A segment can have dependencies. For example: A segment routinely receives some kind of offset in the program, but it has shifted, what should I do now? You can write a mini-bytepatch in SegmentInterpreter :: Before_OEP that will fix the offset to a new one.
  
####
##### Requirements:
 - Visual Studio 17+.
 - MSVC. (x86)
 - Basic knowledge of C ++ / Reverse engineering.

####
##### TO-DO:
 - [ ] Debug-GUI.