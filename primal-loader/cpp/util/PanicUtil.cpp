#include "../../hpp/Vendor.hpp"
#include "../../hpp/loader/runtime/RuntimeHandler.hpp"

void PanicUtil::SetImportant (DWORD *variable, DWORD value, const char* caller, const char* reason) {

    if (variable && value) {
        *variable = value;
    }
    else {
        PanicUtil::Release (Layers::ROUTINE, caller, reason);
    }

}

void PanicUtil::RequireNonNull (Layers layer, DWORD value, const char* caller, const char* reason) {

    if (!value) {
        PanicUtil::Release (layer, caller, reason);
    }

}

void PanicUtil::Release (Layers causedInLayer, const char* caller, const char* reason) {

    Logger& log = Singleton <Logger>::GetInstance ();

    std::stringstream stream;

    stream   
    << "\n" << "\n"
    << "/---------- INFO ---------\\"   << "\n"
    << "|                           "   << "\n"
    << "| Layer:   "  << ParseTypeLayers (causedInLayer) <<  "." << "\n"
    << "| Caused:  "  << reason <<  "." << "\n"
    << "| Call-in: "  << caller <<  "." << "\n"
    << "|                           "   << "\n"
    << "|---------------------------"   << "\n"
    << "|             " << "\n"
    << "| Module:     " << "0x" << std::uppercase << std::hex << reinterpret_cast <DWORD> (Primal::UnCurrentModule) << "." << "\n"
    << "| Allocation: " << "0x" << std::uppercase << std::hex << Primal::UnSegmentAllocate                          << "." << "\n"
    << "|             " << "\n" 
    << "\\--------- INFO ----------/" 
    << "\n" << "\n"
    ;

    log.Info (Logger::Type::EXCEPTION, stream.str().c_str ());

    if (!reinterpret_cast <DWORD> (Primal::UnCurrentModule)) {
        //Debug to process and watch exit code for get solution.
        ExitProcess (0xFFFA1);
    }

    if (!Primal::UnSegmentAllocate) {
        FreeLibraryAndExitThread (reinterpret_cast<HMODULE> (Primal::UnCurrentModule), NULL);
    }

    VirtualFree (reinterpret_cast<LPVOID> (Primal::UnSegmentAllocate), NULL, MEM_RELEASE);
    //Freeze for read log.
    ExitThread (0);

}