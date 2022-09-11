#include "llvm/Transforms/Utils/MyBasicPass2.h"

using namespace llvm;

PreservedAnalyses MyBasicPass2::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  errs() << F.getName() << "\n";
  
  for (Function::iterator bb = F.begin(), e = F.end(); bb != e; ++bb) {
    errs() << "Is this an ertry block: " << bb->isEntryBlock() << "\n";
    for (BasicBlock::iterator i = bb->begin(), e = bb->end(); i != e; ++i) {
      errs() << "Opcode: " << i->getOpcodeName() << "\n";
    } 
  }	
      
  
  return PreservedAnalyses::all();
}


