### Evaluation of vi/vim Recovery Mechanisms:

1. **Swap Files (`.swp`):**  
   Automatically stores uncommitted buffer operations in a hidden file (`.filename.swp`) on disk. During sudden crashes, session reconstruction is achieved via `vi -r filename`.
2. **Persistent Undo (`undodir`):**  
   Saves full edit undo trees to dedicated disk storage. While invaluable for long-term edit tracking across normal closes, standard transient memory undo states disappear during power cuts unless explicitly configured.
3. **Internal Registers:**  
   Volatile RAM storage locations holding yanked, copied, or deleted text blocks. They clear upon power failure and offer zero recovery protection.
4. **Backup Copy System (`~` files):**  
   Creates a snapshot duplicate of the original document upon save. Protects against accidental manual overwrites, but misses changes made between saves during a crash.
5. **Autosave Extensions:**  
   Timer-based plugins that automatically issue disk saves. Effective, but require third-party tool configurations outside native `vi` installs.

---

### Optimal Recovery Strategy & Technical Justification:

**Selected Strategy:** Continuous **Swap File (`.swp`) Recovery** using the shell command:
```bash
vi -r <filename>