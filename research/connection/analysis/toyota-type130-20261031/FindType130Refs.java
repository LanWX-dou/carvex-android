// Read-only Ghidra helper for Toyota libAirPlay.so.
// Usage: FindType130Refs.java <output-file>

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.reloc.Relocation;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import java.io.PrintWriter;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.charset.StandardCharsets;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.Map;
import java.util.Set;

public class FindType130Refs extends GhidraScript {
    private static final String[] NEEDLES = {
        "streams",
        "dataPort",
        "channelID",
        "clientTypeUUID",
        "clientUUID",
        "wantsDedicatedSocket",
        "sendMessageAsIs"
    };

    @Override
    protected void run() throws Exception {
        if (getScriptArgs().length != 1) {
            throw new IllegalArgumentException("Expected output file path");
        }
        PrintWriter out = new PrintWriter(getScriptArgs()[0], "UTF-8");
        try {
            out.println("program=" + currentProgram.getName());
            out.println("language=" + currentProgram.getLanguageID());
            out.println("imageBase=" + currentProgram.getImageBase());
            out.println("=== relevant symbols ===");
            for (ghidra.program.model.symbol.Symbol symbol :
                currentProgram.getSymbolTable().getAllSymbols(true)) {
                String name = symbol.getName(true);
                String lower = name.toLowerCase();
                if (lower.contains("stream") || lower.contains("setup") ||
                    lower.contains("rtsp") || lower.contains("session") ||
                    lower.contains("channel") || lower.contains("iap")) {
                    out.println(symbol.getAddress() + " " + name);
                }
            }

            Map<String, Set<Function>> refsByString = new LinkedHashMap<>();
            for (String needle : NEEDLES) {
                refsByString.put(needle, new LinkedHashSet<>());
            }
            Memory memory = currentProgram.getMemory();
            FunctionManager functions = currentProgram.getFunctionManager();
            Map<Long, String> stringAddresses = new LinkedHashMap<>();
            for (String needle : NEEDLES) {
                byte[] exact = needle.getBytes(StandardCharsets.US_ASCII);
                Address search = currentProgram.getMinAddress();
                while (search != null) {
                    Address stringAddress = memory.findBytes(search, exact, null, true, monitor);
                    if (stringAddress == null) {
                        break;
                    }
                    out.println("string=" + needle + " stringAddress=" + stringAddress);
                    stringAddresses.put(stringAddress.getOffset(), needle);
                    stringAddresses.put(
                        stringAddress.getOffset() - currentProgram.getImageBase().getOffset(),
                        needle);
                    ReferenceIterator directRefs = currentProgram.getReferenceManager()
                        .getReferencesTo(stringAddress);
                    for (Reference ref : directRefs) {
                        Address from = ref.getFromAddress();
                        Function function = functions.getFunctionContaining(from);
                        out.println("  directRef=" + from + " function="
                            + (function == null ? "<none>" : function.getName() + "@"
                            + function.getEntryPoint()));
                        if (function != null) {
                            refsByString.get(needle).add(function);
                        }
                    }
                    byte[] pointer = ByteBuffer.allocate(8)
                        .order(ByteOrder.LITTLE_ENDIAN)
                        .putLong(stringAddress.getOffset())
                        .array();
                    Address pointerSearch = currentProgram.getMinAddress();
                    while (pointerSearch != null) {
                        Address pointerAddress = memory.findBytes(
                            pointerSearch, pointer, null, true, monitor);
                        if (pointerAddress == null) {
                            break;
                        }
                        out.println("  pointer=" + pointerAddress);
                        ReferenceIterator pointerRefs = currentProgram.getReferenceManager()
                            .getReferencesTo(pointerAddress);
                        for (Reference ref : pointerRefs) {
                            Address from = ref.getFromAddress();
                            Function function = functions.getFunctionContaining(from);
                            out.println("    pointerRef=" + from + " function="
                                + (function == null ? "<none>" : function.getName() + "@"
                                + function.getEntryPoint()));
                            if (function != null) {
                                refsByString.get(needle).add(function);
                            }
                        }
                        pointerSearch = pointerAddress.next();
                    }
                    search = stringAddress.next();
                }
            }

            java.util.Iterator<Relocation> relocations =
                currentProgram.getRelocationTable().getRelocations();
            while (relocations.hasNext()) {
                Relocation relocation = relocations.next();
                String matched = null;
                long[] values = relocation.getValues();
                if (values != null) {
                    for (long value : values) {
                        String needle = stringAddresses.get(value);
                        if (needle != null) {
                            matched = needle;
                            break;
                        }
                    }
                }
                if (matched == null &&
                    relocation.getSymbolName() != null &&
                    stringAddresses.values().contains(relocation.getSymbolName())) {
                    matched = relocation.getSymbolName();
                }
                if (matched == null) {
                    continue;
                }
                Address location = relocation.getAddress();
                out.println("relocation string=" + matched + " location=" + location
                    + " type=" + relocation.getType()
                    + " symbol=" + relocation.getSymbolName()
                    + " values=" + java.util.Arrays.toString(values));
                ReferenceIterator relocationRefs = currentProgram.getReferenceManager()
                    .getReferencesTo(location);
                for (Reference ref : relocationRefs) {
                    Address from = ref.getFromAddress();
                    Function function = functions.getFunctionContaining(from);
                    out.println("  relocationRef=" + from + " function="
                        + (function == null ? "<none>" : function.getName() + "@"
                        + function.getEntryPoint()));
                    if (function != null) {
                        refsByString.get(matched).add(function);
                    }
                }
            }

            Set<Function> allFunctions = new LinkedHashSet<>();
            for (Set<Function> values : refsByString.values()) {
                allFunctions.addAll(values);
            }
            for (long offset : new long[] {0x117de8L, 0x128170L}) {
                Address target = currentProgram.getAddressFactory()
                    .getDefaultAddressSpace().getAddress(offset);
                Function function = functions.getFunctionAt(target);
                if (function == null) {
                    function = functions.getFunctionContaining(target);
                }
                if (function != null) {
                    out.println("explicit target=" + target + " function=" + function.getName());
                    allFunctions.add(function);
                } else {
                    out.println("explicit target=" + target + " has no function");
                }
            }
            if (allFunctions.isEmpty()) {
                out.println("No direct references found in defined string data.");
                return;
            }

            DecompInterface decompiler = new DecompInterface();
            decompiler.toggleCCode(true);
            decompiler.toggleSyntaxTree(true);
            if (!decompiler.openProgram(currentProgram)) {
                throw new IllegalStateException("Unable to open decompiler");
            }
            for (Function function : allFunctions) {
                out.println();
                out.println("===== FUNCTION " + function.getName() + " @ "
                    + function.getEntryPoint() + " =====");
                DecompileResults result = decompiler.decompileFunction(function, 120, monitor);
                if (!result.decompileCompleted()) {
                    out.println("decompile failed: " + result.getErrorMessage());
                    continue;
                }
                out.println(result.getDecompiledFunction().getC());
            }
            decompiler.dispose();
        } finally {
            out.close();
        }
    }
}
