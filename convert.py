import os

input_dir = "assets_png/"
# output_dir = "assets/"
output = "assets.h"
with open(output, "wb") as out_f:
    for fn in os.listdir(input_dir):
        with open(os.path.join(input_dir, fn), "rb") as in_f:
            asset_base_fn = fn.replace(".png", "")
            # header_fn = fn.replace(".png", ".h")
            # with open(os.path.join(output_dir, header_fn), "wb") as out_f:
            # print(f'#include "{output_dir}{header_fn}"')
            # print(f'#include "{output_dir}{header_fn}"')
            print(asset_base_fn)
            out_f.write(b"static const unsigned char " + asset_base_fn.encode() + b"[] PROGMEM  = {\n")
            i = -1
            while byte := in_f.read(1):
                pad_str = b", "
                if i == -1:
                    pad_str = b" "
                    i = 0
                elif i == 8:
                    pad_str = b",\n "
                    i = 0
                out_f.write(pad_str + b'0x' + byte.hex().encode())
                i += 1
            out_f.write(b"\n};\n")
            out_f.write(b"uint64_t " + asset_base_fn.encode() + b"_size = sizeof(" + asset_base_fn.encode() + b");\n")
            out_f.write(b"#define I" + asset_base_fn.encode() + b" " + asset_base_fn.encode() + b", " + asset_base_fn.encode() + b"_size\n")
