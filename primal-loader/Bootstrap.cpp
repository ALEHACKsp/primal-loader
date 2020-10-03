#include "hpp/Vendor.hpp"

/**
 *
 *                               ~~~~~~~~~~~
 *                    +----> + < Relocations > + > > >
 * o---------o        |          ~~~~~~~~~~~                    o-----------------------o         o-----------------------o         o----------o
 * [ Segment  > > > > O                              > > > > - | Reconstruct at runtime  | > > > | Call internal framework | > > > | Invoke OEP |
 * o---------o        |          ~~~~~~~~~~~                    o-----------+-----------o         o-----------------------o         o-----+----o
 *                    +----> + <   Imports   > + > > >                      |->  >  >  >  >  >  >  >  >  >  >   <  <  <  <  <  <  <  <  <-|
 *                               ~~~~~~~~~~~ 
 *
 */

BOOL APIENTRY DllMain (HMODULE module, DWORD callReason, LPVOID lpReserved) {
    
    if (callReason == DLL_PROCESS_ATTACH) {

          ///////////////////////////////////////////////////////////////////////////////////////
        //                                                                                      //
        // ROUTINE.                                                                             //
        //                                                                                      //
           Segment segment = Singleton <Segment> :: GetInstance ();                             //
           Logger  log     = Singleton <Logger>  :: GetInstance ();                             //
        //                                                                                      //
        //////////////////////////////////////////////////////////////////////////////////////////
        //                                                                                      //
        //                           SEG    NAD  OAD  SGZ  ALZ  OEP                             //
           RuntimeHandler runtime (segment, 0x0, 0x0, 0x0, 0x0, 0x0);                           //
        //                                                                                      //
        // * SEG - Segment instance.                                                            //
        // * NAD - New allocation address. (Can be 0x0)                                         //
        // * OAD - Old allocation address. (Dump base)                                          //
        // * SGZ - Segment size. (sizeof dump)                                                  //
        // * ALZ - Allocation size. (Should be greater than SGZ if the dump uses alloc as heap) //
        // * OEP - Offset to original entry point.                                              //
        //                                                                                      //
        //////////////////////////////////////////////////////////////////////////////////////////
        //                                                                                      //
        // SEGMENT COMMON ROUTINE.                                                              //
        //                                                                                      //
           SegmentInterpreter framework = Singleton <SegmentInterpreter> :: GetInstance ();     //
        //                                                                                      //
         ///////////////////////////////////////////////////////////////////////////////////////

        //Alloc memory && init variable.
        runtime.ExtractSegment ();

        log.Info (Logger::Type::INFO, "Memory allocated.");

        //Fixup relocs && imports.
        runtime.ReconstructHotPoints ();

        log.Info (Logger::Type::INFO, "Relocations and imports reconstructed.");

        //Fixes, patches, and stuff.
        framework.CallbackWithOEP (SegmentTranslator::CallbackType::BEFORE);
        
        //Make segment alive.
        runtime.InvokeOEP ();

        log.Info (Logger::Type::INFO, "OEP invoked.");

        //Just stuff.
        framework.CallbackWithOEP (SegmentTranslator::CallbackType::AFTER);

    }
    
    return TRUE;

}