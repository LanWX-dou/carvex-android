// Print Ghidra's view of data at addresses: defined data, references, and referenced strings.
// Usage: -postScript DumpAt.java 0x27612fb30 0x2693e7d08
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;

public class DumpAt extends GhidraScript {
    private void showString(Address a) {
        StringBuilder sb = new StringBuilder();
        try {
            for (int i = 0; i < 64; i++) {
                byte b = currentProgram.getMemory().getByte(a.add(i));
                if (b == 0) break;
                if (b < 0x20 || b > 0x7e) return;
                sb.append((char) b);
            }
            if (sb.length() > 0) println("      str=\"" + sb.toString() + "\"");
        } catch (Exception e) {
            // ignore
        }
    }

    public void run() throws Exception {
        var mgr = currentProgram.getReferenceManager();
        for (String raw : getScriptArgs()) {
            Address a = toAddr(Long.parseLong(raw.replace("0x", ""), 16));
            println("=== " + a);
            var d = getDataAt(a);
            if (d == null) {
                println("   data: null");
            } else {
                println("   data: " + d.getDataType().getName());
            }
            for (var r : mgr.getReferencesFrom(a)) {
                Address t = r.getToAddress();
                println("   ref-> " + t);
                if (t != null) {
                    showString(t);
                    for (var r2 : mgr.getReferencesFrom(t)) {
                        println("      " + t + " ref-> " + r2.getToAddress());
                        if (r2.getToAddress() != null) showString(r2.getToAddress());
                    }
                }
            }
        }
    }
}
