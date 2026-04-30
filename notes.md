# srsRAN Developer Notes

## Next Steps
- [x] Port over unit tests
- [ ] Port over e2sm\_ni\_asn1\_packer files and finish implementation
- [ ] Port over E2\_entity changes
- [ ] Implement e2sm\_ni\_ies
- [ ] Port over e2sm\_ni\_impl files and test

## ToDo List

## Working Log
### 20260323
- The \_ies files are all what used to be the E2SM files, defining the ASN.1 encoding scheme.
- The e2sm files been refactored to have shared information elements in the 'common' IEs file.
- I should be able to directly port the ASN.1 encoding from the archive. I just need to check whether a structure already exists in the 'common' file.
>[!WARNING] Lots of errors in e2sm\_ni\_asn1\_packer and a few other files, preventing compile.
- **Next Step:** Finish implementing the ASN.1 encoding definitions in the IEs files.

### 20260322
- Continued to refactor e2sm\_ni\_ies and e2sm\_ni\_asn1\_packer.
- **Next Step:** Figure out how to define the action definitions in e2sm\_ni\_ies.

### 20260321
- Added e2sm\_ni\_ies; formerly e2sm\_ni\\.
- **Next Step:** Continue working on refactoring e2sm\_ni\_asn1\_packer.

### 20260320
- The initial instantiation of the E2SMs seems to happen in the 'e2 factory' files.
- [ ] Need to port over and update e2sm\_ni\_ans1 files to make e2\_du\_factory compile without errors.
- [ ] Need to port over and update e2sm\_ni\_impl files to make e2\_du\_factory compile without errors.
- [ ] Need to implement e2sm\_ni\_control\_service.

### 20260319
- Verified unittests run correctly and there is no regression.
- I have now validated initial functionality of the ngap\_e2\_notifier and e2sm\_ni\_message\_prov units.
- **Next Step:** Port over changes to the E2\_entity and related files.
- e2\_entity has been refactored. I need to make sense of the new software design before I can reimplement my work.

### 20260314
- I was able to fix compile issues with current unit tests
- **Next step:** Run unit tests and verify regression testing.

### 20260311
- Working on fixing unittests
- 
### 20260302
- Started porting over unit tests and confirming regression testing.

### 20260219
- Started porting over changes from old fork to clean branch. No issues so far.


