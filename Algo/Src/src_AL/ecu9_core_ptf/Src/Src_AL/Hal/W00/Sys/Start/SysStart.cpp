#include <ALUnitTest_UserInterface.h>

int main(int argc, char* argv[])
{
  AL_UNITTEST_INIT(argc, argv);

  AL_UNITTEST_ADD_TESTS();

  const boolean boUnitTestRunIsOK = AL_UNITTEST_RUN();

  return ((boUnitTestRunIsOK == TRUE) ? 0 : -1);
}
