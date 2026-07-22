### Commands Executed:
1. `mkdir -p submissions && touch submissions/file1.txt submissions/file2.txt submissions/file3.txt`
2. `echo "data content A" > submissions/file1.txt; echo "data content A" > submissions/file2.txt; echo "data content B" > submissions/file3.txt`
3. `chmod +x process_submissions.sh`
4. `./process_submissions.sh`
5. `cat report.txt`

### Explanations:
* **Cryptographic Hash Tracking (`md5sum` & Associative Arrays):** Uses `md5sum` combined with `awk '{print $1}'` to generate a content-based digital fingerprint for each file. An associative array (`checksum_registry`) tracks seen hashes in $O(1)$ time complexity, isolating duplicate files regardless of their filenames.
* **Stream Separation (`2>> "$ERRORS"`):** Directs Standard Error (file descriptor 2) away from the user interface into `errors.log`, keeping stdout clean while capturing system warnings (e.g., permission failures).
* **Idempotent File Initialization (`>` vs `>>`):** Uses the `>` operator to wipe and reset log files prior to run execution, followed by `>>` to incrementally log updates without losing existing session entries.