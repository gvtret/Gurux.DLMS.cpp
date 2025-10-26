# AGENTS.md — Project Automation Overview

This document describes the automation agents used in the **Gurux DLMS/COSEM C++** project.  
Each agent corresponds to a CMake target and a shell script stored in the `agents/` directory.  
The agents provide a unified, repeatable workflow for building, testing, linting, and documenting the project.

---

## 🧩 Overview

The project is implemented in **C++11** and uses:
- **CMake** — build system and meta-configuration.
- **GoogleTest** — unit and integration test framework.
- **Doxygen** — automatic documentation generation.
- **.clang-format** — enforced code style.

The automation layer ensures that contributors and CI/CD pipelines use the same commands and configuration.

---

## ⚙️ BuildAgent

**Purpose:**  
Compile all targets of the GuruxDLMS library and example applications.

**CMake target:** `build`  
**Script:** `agents/build_agent.sh`

```bash
#!/bin/bash
# ----------------------------------------------------------
# BuildAgent — Configures and builds the GuruxDLMS project.
# ----------------------------------------------------------
set -e
echo "[BuildAgent] Configuring and building GuruxDLMS..."
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel $(nproc)
echo "[BuildAgent] Build completed successfully."
```

**Responsibilities**
- Configure CMake with desired build type (`Debug` or `Release`).
- Compile all targets with `-Wall -Wextra -pedantic`.
- Fail fast on compiler errors.

**Dependencies**
- `cmake >= 3.10`
- `gcc >= 4.9` or `clang >= 3.4`
- `make` or `ninja`

---

## 🧪 TestAgent

**Purpose:**  
Run all GoogleTest-based unit tests through CTest.

**Implementation:**  
CMake target: `test`  
Script: `agents/test_agent.sh`

```bash
#!/bin/bash
# ----------------------------------------------------------
# TestAgent — Runs all unit tests via CTest/GoogleTest.
# ----------------------------------------------------------
set -e
echo "[TestAgent] Running GuruxDLMS tests..."
cd build
ctest --output-on-failure
echo "[TestAgent] All tests passed successfully."
```

**Responsibilities**
- Execute all tests registered with `add_test()` in CMake.
- Collect and display failing test output.

**Dependencies**
- `GoogleTest` (downloaded or prebuilt)
- Built project binaries from `BuildAgent`

**Notes**
All test sources reside in the `tests/` directory, following the project convention.

---

## 🧹 LintAgent

**Purpose:**  
Check formatting and run static analysis to enforce style and correctness.

**Implementation:**  
CMake target: `lint`  
Script: `agents/lint_agent.sh`

```bash
#!/bin/bash
# ----------------------------------------------------------
# LintAgent — Verifies formatting and runs static analysis.
# ----------------------------------------------------------
set -e
echo "[LintAgent] Checking formatting..."
clang-format --dry-run --Werror $(find development/include development/src tests -name '*.cpp' -or -name '*.h')
echo "[LintAgent] Running clang-tidy..."
clang-tidy $(find development/src -name '*.cpp') -- -Idevelopment/include -std=c++11
echo "[LintAgent] Linting completed successfully."
```

**Responsibilities**
- Validate code style against `.clang-format`
- Perform static analysis via `clang-tidy`
- Enforce `C++11` compliance

**Dependencies**
- `clang-format`
- `clang-tidy`
- Optional: `cppcheck` for deeper static analysis

---

## 📘 DocAgent

**Purpose:**  
Generate project documentation using **Doxygen** via the `doc` CMake target.

**Implementation:**  
CMake target: `doc`  
Script: `agents/doc_agent.sh`

```bash
#!/bin/bash
# ----------------------------------------------------------
# DocAgent — Generates API documentation using Doxygen.
# ----------------------------------------------------------
set -e
echo "[DocAgent] Generating documentation..."
if ! command -v doxygen >/dev/null; then
  echo "Error: Doxygen not installed. Install with 'sudo apt install doxygen graphviz'."
  exit 1
fi
cd build
doxygen Doxyfile
echo "[DocAgent] Documentation generated at build/docs/html"
```

**Responsibilities**
- Run Doxygen with the project configuration
- Generate HTML documentation under `build/docs/html`
- Optionally render UML diagrams using PlantUML (if configured)

**Dependencies**
- `doxygen`
- `dot`
- `graphviz` (for class and call graphs)
- `plantuml` (optional)

---

## 🧩 Integration in CMakeLists.txt

All agents are registered as CMake custom targets.  
Append the following to your `CMakeLists.txt`:

```cmake
# ----------------------------------------------------------
# Agents (Build, Test, Lint, Doc)
# ----------------------------------------------------------

set(AGENTS_DIR ${CMAKE_SOURCE_DIR}/agents)

add_custom_target(build
  COMMAND bash ${AGENTS_DIR}/build_agent.sh
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Running BuildAgent (CMake build wrapper)"
  VERBATIM)

add_custom_target(test
  COMMAND bash ${AGENTS_DIR}/test_agent.sh
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Running TestAgent (GoogleTest + CTest)"
  VERBATIM)

add_custom_target(lint
  COMMAND bash ${AGENTS_DIR}/lint_agent.sh
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Running LintAgent (clang-format + clang-tidy)"
  VERBATIM)

add_custom_target(doc
  COMMAND bash ${AGENTS_DIR}/doc_agent.sh
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Running DocAgent (Doxygen documentation generator)"
  VERBATIM)
```

---

## 🧱 Directory Layout

```
./
├── .clang-format
├── .gitattributes
├── .gitignore
├── CMakeLists.txt
├── CREDITS.md
├── Doxyfile.in
├── GuruxDLMSClientExample/
│   ├── CMakeLists.txt
│   ├── VS/
│   │   ├── GuruxDLMClientExample.sln
│   │   ├── GuruxDLMSClientExample.vcxproj
│   │   └── GuruxDLMSClientExample.vcxproj.filters
│   ├── include/
│   │   ├── communication.h
│   │   └── getopt.h
│   ├── makefile
│   └── src/
│       ├── GuruxDLMSClientExample.cpp
│       ├── communication.cpp
│       └── getopt.c
├── GuruxDLMSMeterListener/
│   ├── VS/
│   │   ├── GuruxDLMSMeterListener.sln
│   │   ├── GuruxDLMSMeterListener.vcxproj
│   │   └── GuruxDLMSMeterListener.vcxproj.filters
│   ├── include/
│   │   ├── GXDLMSMeterListener.h
│   │   ├── communication.h
│   │   └── getopt.h
│   ├── makefile
│   └── src/
│       ├── GXDLMSMeterListener.cpp
│       ├── communication.cpp
│       ├── getopt.c
│       └── main.cpp
├── GuruxDLMSPushExample/
│   ├── CMakeLists.txt
│   ├── VS/
│   │   ├── GuruxDLMSPushExample.sln
│   │   ├── GuruxDLMSPushExample.vcxproj
│   │   └── GuruxDLMSPushExample.vcxproj.filters
│   ├── include/
│   │   └── GXDLMSPushListener.h
│   ├── makefile
│   └── src/
│       ├── GXDLMSPushListener.cpp
│       └── main.cpp
├── GuruxDLMSServerExample/
│   ├── CMakeLists.txt
│   ├── VS/
│   │   ├── GuruxDLMSServerExample.sln
│   │   ├── GuruxDLMSServerExample.vcxproj
│   │   └── GuruxDLMSServerExample.vcxproj.filters
│   ├── include/
│   │   ├── GXDLMSBase.h
│   │   ├── GXDLMSServerLN.h
│   │   ├── GXDLMSServerLN_47.h
│   │   ├── GXDLMSServerSN.h
│   │   ├── GXDLMSServerSN_47.h
│   │   └── getopt.h
│   ├── makefile
│   └── src/
│       ├── GXDLMSBase.cpp
│       ├── getopt.c
│       └── main.cpp
├── LICENSE
├── LICENSE.txt
├── README.md
├── development/
│   ├── VS/
│   │   ├── GuruxDLMS.sln
│   │   ├── GuruxDLMS.vcproj
│   │   ├── GuruxDLMS.vcxproj
│   │   └── GuruxDLMS.vcxproj.filters
│   ├── include/
│   │   ├── GXAPDU.h
│   │   ├── GXAdjacentCell.h
│   │   ├── GXApplicationContextName.h
│   │   ├── GXAsn1Base.h
│   │   ├── GXAsn1BitString.h
│   │   ├── GXAsn1Context.h
│   │   ├── GXAsn1Converter.h
│   │   ├── GXAsn1Helpers.h
│   │   ├── GXAsn1Ia5String.h
│   │   ├── GXAsn1Integer.h
│   │   ├── GXAsn1ObjectIdentifier.h
│   │   ├── GXAsn1Sequence.h
│   │   ├── GXAsn1Set.h
│   │   ├── GXAsn1Time.h
│   │   ├── GXAsn1Utf8String.h
│   │   ├── GXAsn1Variant.h
│   │   ├── GXAttributeCollection.h
│   │   ├── GXAuthentication.h
│   │   ├── GXAuthenticationMechanismName.h
│   │   ├── GXBigInteger.h
│   │   ├── GXBitString.h
│   │   ├── GXByteArray.h
│   │   ├── GXBytebuffer.h
│   │   ├── GXCertificateRequest.h
│   │   ├── GXChargePerUnitScaling.h
│   │   ├── GXChargeTable.h
│   │   ├── GXCipher.h
│   │   ├── GXCommodity.h
│   │   ├── GXCreditChargeConfiguration.h
│   │   ├── GXCurrency.h
│   │   ├── GXCurve.h
│   │   ├── GXDLMS.h
│   │   ├── GXDLMSAccessItem.h
│   │   ├── GXDLMSAccount.h
│   │   ├── GXDLMSActionItem.h
│   │   ├── GXDLMSActionSchedule.h
│   │   ├── GXDLMSActionSet.h
│   │   ├── GXDLMSActivityCalendar.h
│   │   ├── GXDLMSArbitrator.h
│   │   ├── GXDLMSAssociationLogicalName.h
│   │   ├── GXDLMSAssociationShortName.h
│   │   ├── GXDLMSAttribute.h
│   │   ├── GXDLMSAutoAnswer.h
│   │   ├── GXDLMSAutoConnect.h
│   │   ├── GXDLMSCaptureObject.h
│   │   ├── GXDLMSCertificateInfo.h
│   │   ├── GXDLMSCharge.h
│   │   ├── GXDLMSClient.h
│   │   ├── GXDLMSClock.h
│   │   ├── GXDLMSCommunicationPortProtection.h
│   │   ├── GXDLMSCompactData.h
│   │   ├── GXDLMSConnectionEventArgs.h
│   │   ├── GXDLMSContextType.h
│   │   ├── GXDLMSConverter.h
│   │   ├── GXDLMSCredit.h
│   │   ├── GXDLMSData.h
│   │   ├── GXDLMSDataProtectionAgreedKey.h
│   │   ├── GXDLMSDataProtectionIdentifiedKey.h
│   │   ├── GXDLMSDataProtectionKey.h
│   │   ├── GXDLMSDataProtectionWrappeddKey.h
│   │   ├── GXDLMSDayProfile.h
│   │   ├── GXDLMSDayProfileAction.h
│   │   ├── GXDLMSDemandRegister.h
│   │   ├── GXDLMSDisconnectControl.h
│   │   ├── GXDLMSEmergencyProfile.h
│   │   ├── GXDLMSExtendedRegister.h
│   │   ├── GXDLMSGPRSSetup.h
│   │   ├── GXDLMSGSMCellInfo.h
│   │   ├── GXDLMSGSMDiagnostic.h
│   │   ├── GXDLMSHdlcSetup.h
│   │   ├── GXDLMSIECOpticalPortSetup.h
│   │   ├── GXDLMSIec8802LlcType1Setup.h
│   │   ├── GXDLMSIec8802LlcType2Setup.h
│   │   ├── GXDLMSIec8802LlcType3Setup.h
│   │   ├── GXDLMSIecTwistedPairSetup.h
│   │   ├── GXDLMSImageActivateInfo.h
│   │   ├── GXDLMSImageTransfer.h
│   │   ├── GXDLMSIp4Setup.h
│   │   ├── GXDLMSIp4SetupIpOption.h
│   │   ├── GXDLMSIp6Setup.h
│   │   ├── GXDLMSLNCommandHandler.h
│   │   ├── GXDLMSLNParameters.h
│   │   ├── GXDLMSLimiter.h
│   │   ├── GXDLMSLimits.h
│   │   ├── GXDLMSLlcSscsSetup.h
│   │   ├── GXDLMSLongTransaction.h
│   │   ├── GXDLMSMBusClient.h
│   │   ├── GXDLMSMBusMasterPortSetup.h
│   │   ├── GXDLMSMBusSlavePortSetup.h
│   │   ├── GXDLMSMacAddressSetup.h
│   │   ├── GXDLMSMd5.h
│   │   ├── GXDLMSMessageHandler.h
│   │   ├── GXDLMSModemConfiguration.h
│   │   ├── GXDLMSModemInitialisation.h
│   │   ├── GXDLMSMonitoredValue.h
│   │   ├── GXDLMSNotify.h
│   │   ├── GXDLMSNtpSetup.h
│   │   ├── GXDLMSObject.h
│   │   ├── GXDLMSObjectCollection.h
│   │   ├── GXDLMSObjectDefinition.h
│   │   ├── GXDLMSObjectFactory.h
│   │   ├── GXDLMSParameterMonitor.h
│   │   ├── GXDLMSPlcMeterInfo.h
│   │   ├── GXDLMSPlcRegister.h
│   │   ├── GXDLMSPppSetup.h
│   │   ├── GXDLMSPppSetupIPCPOption.h
│   │   ├── GXDLMSPppSetupLcpOption.h
│   │   ├── GXDLMSPrimeNbOfdmPlcApplicationsIdentification.h
│   │   ├── GXDLMSPrimeNbOfdmPlcMacCounters.h
│   │   ├── GXDLMSPrimeNbOfdmPlcMacFunctionalParameters.h
│   │   ├── GXDLMSPrimeNbOfdmPlcMacNetworkAdministrationData.h
│   │   ├── GXDLMSPrimeNbOfdmPlcMacSetup.h
│   │   ├── GXDLMSPrimeNbOfdmPlcPhysicalLayerCounters.h
│   │   ├── GXDLMSProfileGeneric.h
│   │   ├── GXDLMSPushObject.h
│   │   ├── GXDLMSPushSetup.h
│   │   ├── GXDLMSQualityOfService.h
│   │   ├── GXDLMSRegister.h
│   │   ├── GXDLMSRegisterActivation.h
│   │   ├── GXDLMSRegisterMonitor.h
│   │   ├── GXDLMSSFSKActiveInitiator.h
│   │   ├── GXDLMSSFSKMacCounters.h
│   │   ├── GXDLMSSFSKMacSynchronizationTimeouts.h
│   │   ├── GXDLMSSFSKPhyMacSetUp.h
│   │   ├── GXDLMSSFSKReportingSystemList.h
│   │   ├── GXDLMSSNCommandHandler.h
│   │   ├── GXDLMSSNParameters.h
│   │   ├── GXDLMSSapAssignment.h
│   │   ├── GXDLMSSchedule.h
│   │   ├── GXDLMSScheduleEntry.h
│   │   ├── GXDLMSScript.h
│   │   ├── GXDLMSScriptAction.h
│   │   ├── GXDLMSScriptTable.h
│   │   ├── GXDLMSSeasonProfile.h
│   │   ├── GXDLMSSecureClient.h
│   │   ├── GXDLMSSecureServer.h
│   │   ├── GXDLMSSecuritySetup.h
│   │   ├── GXDLMSServer.h
│   │   ├── GXDLMSSettings.h
│   │   ├── GXDLMSSha1.h
│   │   ├── GXDLMSSha256.h
│   │   ├── GXDLMSSha384.h
│   │   ├── GXDLMSSpecialDay.h
│   │   ├── GXDLMSSpecialDaysTable.h
│   │   ├── GXDLMSTarget.h
│   │   ├── GXDLMSTcpUdpSetup.h
│   │   ├── GXDLMSTokenGateway.h
│   │   ├── GXDLMSTranslator.h
│   │   ├── GXDLMSTranslatorStructure.h
│   │   ├── GXDLMSUtilityTables.h
│   │   ├── GXDLMSValueEventArg.h
│   │   ├── GXDLMSValueEventCollection.h
│   │   ├── GXDLMSVariant.h
│   │   ├── GXDLMSWeekProfile.h
│   │   ├── GXDataInfo.h
│   │   ├── GXDate.h
│   │   ├── GXDateTime.h
│   │   ├── GXEccPoint.h
│   │   ├── GXEcdsa.h
│   │   ├── GXHdlcSettings.h
│   │   ├── GXHelpers.h
│   │   ├── GXIgnore.h
│   │   ├── GXMBusClientData.h
│   │   ├── GXMacAvailableSwitch.h
│   │   ├── GXMacDirectTable.h
│   │   ├── GXMacMulticastEntry.h
│   │   ├── GXMacPhyCommunication.h
│   │   ├── GXNeighborDiscoverySetup.h
│   │   ├── GXPkcs10.h
│   │   ├── GXPkcs8.h
│   │   ├── GXPlcSettings.h
│   │   ├── GXPrivateKey.h
│   │   ├── GXPublicKey.h
│   │   ├── GXPushConfirmationParameter.h
│   │   ├── GXPushProtectionParameters.h
│   │   ├── GXRepetitionDelay.h
│   │   ├── GXReplyData.h
│   │   ├── GXSNInfo.h
│   │   ├── GXSecure.h
│   │   ├── GXSerialNumberCounter.h
│   │   ├── GXServerReply.h
│   │   ├── GXShamirs.h
│   │   ├── GXStandardObisCode.h
│   │   ├── GXStandardObisCodeCollection.h
│   │   ├── GXTime.h
│   │   ├── GXTokenGatewayConfiguration.h
│   │   ├── GXUnitCharge.h
│   │   ├── GXXmlReader.h
│   │   ├── GXXmlWriter.h
│   │   ├── GXXmlWriterSettings.h
│   │   ├── GXx509Certificate.h
│   │   ├── IGXDLMSBase.h
│   │   ├── OBiscodes.h
│   │   ├── TranslatorGeneralTags.h
│   │   ├── TranslatorSimpleTags.h
│   │   ├── TranslatorStandardTags.h
│   │   ├── TranslatorTags.h
│   │   ├── chipperingenums.h
│   │   ├── enums.h
│   │   └── errorcodes.h
│   ├── makefile
│   └── src/
│       ├── GXAPDU.cpp
│       ├── GXAdjacentCell.cpp
│       ├── GXApplicationContextName.cpp
│       ├── GXAsn1Context.cpp
│       ├── GXAsn1Converter.cpp
│       ├── GXAsn1Variant.cpp
│       ├── GXAuthenticationMechanismName.cpp
│       ├── GXBigInteger.cpp
│       ├── GXBitString.cpp
│       ├── GXByteArray.cpp
│       ├── GXBytebuffer.cpp
│       ├── GXChargePerUnitScaling.cpp
│       ├── GXChargeTable.cpp
│       ├── GXCipher.cpp
│       ├── GXCommodity.cpp
│       ├── GXCreditChargeConfiguration.cpp
│       ├── GXCurrency.cpp
│       ├── GXDLMS.cpp
│       ├── GXDLMSAccessItem.cpp
│       ├── GXDLMSAccount.cpp
│       ├── GXDLMSActionItem.cpp
│       ├── GXDLMSActionSchedule.cpp
│       ├── GXDLMSActionSet.cpp
│       ├── GXDLMSActivityCalendar.cpp
│       ├── GXDLMSArbitrator.cpp
│       ├── GXDLMSAssociationLogicalName.cpp
│       ├── GXDLMSAssociationShortName.cpp
│       ├── GXDLMSAutoAnswer.cpp
│       ├── GXDLMSAutoConnect.cpp
│       ├── GXDLMSCaptureObject.cpp
│       ├── GXDLMSCertificateInfo.cpp
│       ├── GXDLMSCharge.cpp
│       ├── GXDLMSClient.cpp
│       ├── GXDLMSClock.cpp
│       ├── GXDLMSCommunicationPortProtection.cpp
│       ├── GXDLMSCompactData.cpp
│       ├── GXDLMSContextType.cpp
│       ├── GXDLMSConverter.cpp
│       ├── GXDLMSCredit.cpp
│       ├── GXDLMSData.cpp
│       ├── GXDLMSDayProfile.cpp
│       ├── GXDLMSDayProfileAction.cpp
│       ├── GXDLMSDemandRegister.cpp
│       ├── GXDLMSDisconnectControl.cpp
│       ├── GXDLMSEmergencyProfile.cpp
│       ├── GXDLMSExtendedRegister.cpp
│       ├── GXDLMSGPRSSetup.cpp
│       ├── GXDLMSGSMCellInfo.cpp
│       ├── GXDLMSGSMDiagnostic.cpp
│       ├── GXDLMSHdlcSetup.cpp
│       ├── GXDLMSIECOpticalPortSetup.cpp
│       ├── GXDLMSIec8802LlcType1Setup.cpp
│       ├── GXDLMSIec8802LlcType2Setup.cpp
│       ├── GXDLMSIec8802LlcType3Setup.cpp
│       ├── GXDLMSIecTwistedPairSetup.cpp
│       ├── GXDLMSImageActivateInfo.cpp
│       ├── GXDLMSImageTransfer.cpp
│       ├── GXDLMSIp4Setup.cpp
│       ├── GXDLMSIp4SetupIpOption.cpp
│       ├── GXDLMSIp6Setup.cpp
│       ├── GXDLMSLNCommandHandler.cpp
│       ├── GXDLMSLNParameters.cpp
│       ├── GXDLMSLimiter.cpp
│       ├── GXDLMSLlcSscsSetup.cpp
│       ├── GXDLMSMBusClient.cpp
│       ├── GXDLMSMBusMasterPortSetup.cpp
│       ├── GXDLMSMBusSlavePortSetup.cpp
│       ├── GXDLMSMacAddressSetup.cpp
│       ├── GXDLMSMd5.cpp
│       ├── GXDLMSMessageHandler.cpp
│       ├── GXDLMSModemConfiguration.cpp
│       ├── GXDLMSModemInitialisation.cpp
│       ├── GXDLMSMonitoredValue.cpp
│       ├── GXDLMSNotify.cpp
│       ├── GXDLMSNtpSetup.cpp
│       ├── GXDLMSObject.cpp
│       ├── GXDLMSObjectCollection.cpp
│       ├── GXDLMSObjectDefinition.cpp
│       ├── GXDLMSObjectFactory.cpp
│       ├── GXDLMSParameterMonitor.cpp
│       ├── GXDLMSPppSetup.cpp
│       ├── GXDLMSPppSetupIPCPOption.cpp
│       ├── GXDLMSPppSetupLcpOption.cpp
│       ├── GXDLMSPrimeNbOfdmPlcApplicationsIdentification.cpp
│       ├── GXDLMSPrimeNbOfdmPlcMacCounters.cpp
│       ├── GXDLMSPrimeNbOfdmPlcMacFunctionalParameters.cpp
│       ├── GXDLMSPrimeNbOfdmPlcMacNetworkAdministrationData.cpp
│       ├── GXDLMSPrimeNbOfdmPlcMacSetup.cpp
│       ├── GXDLMSPrimeNbOfdmPlcPhysicalLayerCounters.cpp
│       ├── GXDLMSProfileGeneric.cpp
│       ├── GXDLMSPushObject.cpp
│       ├── GXDLMSPushSetup.cpp
│       ├── GXDLMSQualityOfService.cpp
│       ├── GXDLMSRegister.cpp
│       ├── GXDLMSRegisterActivation.cpp
│       ├── GXDLMSRegisterMonitor.cpp
│       ├── GXDLMSSFSKActiveInitiator.cpp
│       ├── GXDLMSSFSKMacCounters.cpp
│       ├── GXDLMSSFSKMacSynchronizationTimeouts.cpp
│       ├── GXDLMSSFSKPhyMacSetUp.cpp
│       ├── GXDLMSSFSKReportingSystemList.cpp
│       ├── GXDLMSSNCommandHandler.cpp
│       ├── GXDLMSSNParameters.cpp
│       ├── GXDLMSSapAssignment.cpp
│       ├── GXDLMSSchedule.cpp
│       ├── GXDLMSScheduleEntry.cpp
│       ├── GXDLMSScript.cpp
│       ├── GXDLMSScriptAction.cpp
│       ├── GXDLMSScriptTable.cpp
│       ├── GXDLMSSeasonProfile.cpp
│       ├── GXDLMSSecureClient.cpp
│       ├── GXDLMSSecureServer.cpp
│       ├── GXDLMSSecuritySetup.cpp
│       ├── GXDLMSServer.cpp
│       ├── GXDLMSSettings.cpp
│       ├── GXDLMSSha1.cpp
│       ├── GXDLMSSha256.cpp
│       ├── GXDLMSSha384.cpp
│       ├── GXDLMSSpecialDay.cpp
│       ├── GXDLMSSpecialDaysTable.cpp
│       ├── GXDLMSTarget.cpp
│       ├── GXDLMSTcpUdpSetup.cpp
│       ├── GXDLMSTokenGateway.cpp
│       ├── GXDLMSTranslator.cpp
│       ├── GXDLMSTranslatorStructure.cpp
│       ├── GXDLMSUtilityTables.cpp
│       ├── GXDLMSValueEventArg.cpp
│       ├── GXDLMSVariant.cpp
│       ├── GXDLMSWeekProfile.cpp
│       ├── GXDateTime.cpp
│       ├── GXEcdsa.cpp
│       ├── GXHdlcSettings.cpp
│       ├── GXHelpers.cpp
│       ├── GXPkcs10.cpp
│       ├── GXPkcs8.cpp
│       ├── GXPlcSettings.cpp
│       ├── GXPrivateKey.cpp
│       ├── GXPublicKey.cpp
│       ├── GXReplyData.cpp
│       ├── GXSNInfo.cpp
│       ├── GXSecure.cpp
│       ├── GXSerialNumberCounter.cpp
│       ├── GXShamirs.cpp
│       ├── GXStandardObisCode.cpp
│       ├── GXStandardObisCodeCollection.cpp
│       ├── GXTokenGatewayConfiguration.cpp
│       ├── GXUnitCharge.cpp
│       ├── GXXmlReader.cpp
│       ├── GXXmlWriter.cpp
│       ├── GXXmlWriterSettings.cpp
│       └── GXx509Certificate.cpp
├── mbed/
│   └── GuruxDLMSClientExample/
│       ├── communication.cpp
│       ├── communication.h
│       ├── main.cpp
│       ├── mbed-os.lib
│       └── mbed_settings.py
├── print_size.cmake
├── tests/
│   ├── CMakeLists.txt
│   ├── GXAPDUTest.cpp
│   └── GXByteBufferTest.cpp
└── tree.txt
```

---

## 🧩 Example Doxyfile.in

```ini
PROJECT_NAME           = MyProject
OUTPUT_DIRECTORY       = build/docs
INPUT                  = src include
FILE_PATTERNS          = *.h *.cpp
RECURSIVE              = YES
GENERATE_LATEX         = NO
GENERATE_HTML          = YES
EXTRACT_PRIVATE        = YES
EXTRACT_STATIC         = YES
HAVE_DOT               = YES
DOT_IMAGE_FORMAT       = svg
CALL_GRAPH             = YES
CALLER_GRAPH           = YES
GENERATE_TREEVIEW      = YES
QUIET                  = YES
PLANTUML_JAR_PATH      = /usr/share/plantuml/plantuml.jar
```

---

## 🧩 Local Usage

Typical developer workflow:

```bash
# Build project
cmake --build . --target all

# Run unit tests
cmake --build . --target test

# Check formatting and static analysis
cmake --build . --target lint

# Generate documentation
cmake --build . --target doc
```

Each agent can also be executed manually via its shell script in `agents/`.

---

## 🧠 Summary

| Agent        | Purpose                         | Trigger       | Key Tools             |
|---------------|---------------------------------|----------------|------------------------|
| BuildAgent    | Configure and compile project   | `make build`   | `cmake`, `gcc/clang`  |
| TestAgent     | Execute unit/integration tests  | `make test`    | `ctest`, `gtest`      |
| LintAgent     | Format & static analysis check  | `make lint`    | `clang-format`, `clang-tidy` |
| DocAgent      | Generate HTML documentation     | `make doc`     | `doxygen`, `graphviz` |

---

## 🧩 Notes

- All agents fail immediately on errors (`set -e`).
- Logs are stored under `build/logs/` if present.
- The `.clang-format` file defines the canonical code style — all contributors must use it before commit.
- The documentation target (`doc`) is always optional, but CI pipelines must verify it builds without warnings.

---

CodexAI-style automation — simple agents, one responsibility each.  
Every engineer can inspect, run, and extend them without surprises.
