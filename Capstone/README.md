# FORENSIX – Uploaded Evidence Monitoring Upgrade

Complete source project. Extract into a new folder. Open CMD in that folder. Existing evidence can be migrated by copying storage while both servers are stopped.

## Windows build

Open a Visual Studio Developer Command Prompt:

```cmd
cmake -S . -B build -A x64 -DCMAKE_TOOLCHAIN_FILE="C:/Users/Lenovo 14/Downloads/vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows -DVCPKG_INSTALLED_DIR="C:/Users/Lenovo 14/Downloads/FORENSIX_CPP/build/vcpkg_installed"
cmake --build build --config Release
build\Release\forensix.exe
```

Open http://localhost:5000. Run `pdftotext -v` to verify Poppler is available.

## New API endpoints

- `GET /api/monitor/status`
- `POST /api/monitor/start`
- `POST /api/monitor/stop`
- `GET /api/monitor/events`

## Monitoring behavior

- A worker thread hashes each registered monitored file every two seconds.
- New uploads are registered and logged.
- Modified, deleted and restored file events are written to `storage/metadata/events.txt`.
- History survives restart; the observation baseline is reset at startup. Changes while the server is offline are still detectable by the hash integrity check, but do not create retroactive events.
- Starting monitoring establishes a new observation baseline. Changes made while monitoring was stopped are not emitted as historical events.
- `storage/originals` is the trusted evidence baseline and should be protected with OS permissions for production use.
- This is polling, not Windows kernel event monitoring. Changes that occur and revert between polls can be missed.
- The comparison engine uses bounded Myers alignment (edit-distance limit 300). For extensive edits it returns a combined changed region.
- PDF text extraction uses `pdftotext`. Scanned PDFs, images, and DOCX contents are not compared as text.
- This is a local demonstration system, not a hardened multi-user forensic evidence platform. No authentication is implemented.

## Test

1. Upload `Original_Report.pdf`.
2. Click Upload Modified and select `Modified_Report.pdf`.
3. The status and event history update automatically.
4. Click Compare to view original and modified text.
5. You can also modify `storage/monitored/<evidence-id>.bin` while the server is running. Do not edit `storage/originals`.
