; ModuleID = 'binary.c'
source_filename = "binary.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [7 x i8] c"HELLO\0A\00", align 1
@.str.1 = private unnamed_addr constant [16 x i8] c"running second\0A\00", align 1
@.str.2 = private unnamed_addr constant [22 x i8] c"hello from second %d\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store volatile i32 11, i32* %2, align 4
  %4 = load volatile i32, i32* %2, align 4
  %5 = add nsw i32 %4, 1
  store volatile i32 %5, i32* %2, align 4
  %6 = load volatile i32, i32* %2, align 4
  %7 = add nsw i32 %6, 1
  store volatile i32 %7, i32* %2, align 4
  %8 = load volatile i32, i32* %2, align 4
  %9 = add nsw i32 %8, 1
  store volatile i32 %9, i32* %2, align 4
  %10 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i64 0, i64 0))
  %11 = call i32 @second()
  store i32 %11, i32* %3, align 4
  %12 = load i32, i32* %3, align 4
  %13 = add nsw i32 %12, 23
  store i32 %13, i32* %3, align 4
  ret i32 0
}

declare i32 @printf(i8* noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @second() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.1, i64 0, i64 0))
  store i32 3, i32* %1, align 4
  store i32 5, i32* %2, align 4
  store i32 8, i32* %3, align 4
  %5 = load i32, i32* %1, align 4
  %6 = load i32, i32* %2, align 4
  %7 = add nsw i32 %5, %6
  %8 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.2, i64 0, i64 0), i32 noundef %7)
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 14.0.0-1ubuntu1"}
