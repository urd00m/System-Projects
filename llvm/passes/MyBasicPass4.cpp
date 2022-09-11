#include "llvm/Transforms/Utils/MyBasicPass4.h"

using namespace llvm;

bool MyBasicPass4::runOnModule(Module& M) {
  bool inserted_into_function = false;

  // Get context
  auto &CTX = M.getContext();

  /*
    SETTING UP PRINTF
   */
  
  // create i8* (pointer to 8 bits, or char*) 
  PointerType *PrintfArgTy = PointerType::getUnqual(Type::getInt8Ty(CTX));
  
  // create printf declaration (returns i32 or int, takes in char*, and has variable args)
  FunctionType *PrintfTy = FunctionType::get( 
      IntegerType::getInt32Ty(CTX),
      PrintfArgTy,
      /*IsVarArgs=*/true);

  // insert printf declaration
  FunctionCallee Printf = M.getOrInsertFunction("printf", PrintfTy);

  // modify printf attributes (how to call the function) 
  Function *PrintfF = dyn_cast<Function>(Printf.getCallee());
  PrintfF->setDoesNotThrow();
  PrintfF->addParamAttr(0, Attribute::NoCapture);
  PrintfF->addParamAttr(0, Attribute::ReadOnly);


  /*
    PRINTF FORMAT STRING
  */

  // creates the format string 
  llvm::Constant *PrintfFormatStr = llvm::ConstantDataArray::getString(CTX, "(llvm) Hello from: %s\n(llvm)   number of arguments: %d\n");

  // inject format string (injected as PrintfFormatStr as type string) variable
  // TODO llvm::Constant? 
  Constant *PrintfFormatStrVar = M.getOrInsertGlobal("PrintfFormatStr", PrintfFormatStr->getType());

  // Initialize global variable
  dyn_cast<GlobalVariable>(PrintfFormatStrVar)->setInitializer(PrintfFormatStr);

  
  /*
    FUNCTION CALLS IN FUNCTIONS
  */

  // iterate through all the functions in module 
  for(auto& F : M) {
    if(F.isDeclaration()) continue; // has to be a non-declaration function

    // IR builder set to the top of the function
    IRBuilder<> Builder(&*F.getEntryBlock().getFirstInsertionPt());

    // create a global string with func name
    auto FuncName = Builder.CreateGlobalStringPtr(F.getName());

    // debug
    errs() << "Running transformation on pass " << F.getName() << "\n";
    
    // casting, PrintfFormatStrVar is an array of chars we need a pointer to chars 
    llvm::Value *FormatStrPtr = Builder.CreatePointerCast(PrintfFormatStrVar, PrintfArgTy, "formatStr");

    // inject printf call (function call, args)
    Builder.CreateCall(Printf, {FormatStrPtr, FuncName, Builder.getInt32(F.arg_size())});

    // mark as inserted
    inserted_into_function = true;
  }
  
  return inserted_into_function;
}

PreservedAnalyses MyBasicPass4::run(Module& M, ModuleAnalysisManager& MAM) {
  bool changed = runOnModule(M);

  return changed ? PreservedAnalyses::none() : PreservedAnalyses::all();
}
