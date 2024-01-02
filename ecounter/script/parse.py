import os
import sys

def _load_file(file_path):
    if not os.path.exists(file_path):
        print('File not found: {}'.format(file_path))
        sys.exit(1)
    with open(file_path, 'rb') as f:
        data = f.read()
    return data

def _parse_from_binary_dump(data):
    bit_length = 32
    bit_order = 'little'

    # identify the machine bit length
    if data[0x04] == 0x17:
        bit_length = 32
    elif data[0x08] == 0x17:
        bit_length = 64
    else:
        print('Unknown machine bit length')
        sys.exit(1)
    print('Machine bit length: {}'.format(bit_length))
    
    # combine the marker as little endian
    marker = int.from_bytes(data[bit_length//8:bit_length//8 + 4], bit_order)

    # identify the endian marker
    if marker == 0x175BB517:
        bit_order = 'little'
    elif marker == 0x17B55B17:
        bit_order = 'big'
    else:
        print('Unknown endian marker')
        sys.exit(1)
    print("Machine bit order: {}".format(bit_order))

    # parse header
    items_offset = 0
    items_base = int.from_bytes(data[items_offset:items_offset + bit_length // 8], bit_order)

    item_size_offset = items_offset + bit_length // 8 + 4; # offset = items_base + marker
    item_size = int.from_bytes(data[item_size_offset:item_size_offset + 4], bit_order)

    item_cap_offset = item_size_offset + 4;
    item_cap = int.from_bytes(data[item_cap_offset:item_cap_offset + 4], bit_order)

    item_start_offset = item_cap_offset + 8;
    item_start = int.from_bytes(data[item_start_offset:item_start_offset + bit_length // 8], bit_order)

    item_end_offset = item_start_offset + bit_length // 8;
    item_end = int.from_bytes(data[item_end_offset:item_end_offset + bit_length // 8], bit_order)

    item_cap_end_offset = item_end_offset + bit_length // 8;
    item_cap_end = int.from_bytes(data[item_cap_end_offset:item_cap_end_offset + bit_length // 8], bit_order)

    print('item_size: 0x{:08X}'.format(item_size))
    print('item_cap: 0x{:08X}'.format(item_cap))
    print('item_base: 0x{:08X}'.format(items_base))
    print('item_start: 0x{:08X}'.format(item_start))
    print('item_end: 0x{:08X}'.format(item_end))
    print('item_cap_end: 0x{:08X}'.format(item_cap_end))
    start_idx = (item_start - items_base) // item_size
    end_idx = (item_end - items_base) // item_size
    print('items range: {}~{}'.format(start_idx, end_idx))
    print('items number: {}'.format((end_idx + item_cap - start_idx) % item_cap))

    # parse items
    data_offset = item_cap_end_offset + 3 * bit_length // 8
    items = []
    for i in range(item_cap):
        item_offset = data_offset + i * item_size
        item = int.from_bytes(data[item_offset:item_offset + item_size], bit_order)
        items.append(item) 
        print('parsing data...from: 0x{:08X} to: 0x{:08X} value: 0x{:08X}'.format(item_offset, item_offset + item_size, item))
    
    # re-order items
    if start_idx > end_idx:
        items = items[start_idx:] + items[:end_idx]
    else:
        items = items[start_idx:end_idx]
    
    return items


def parse(file_path):
    data = _load_file(file_path)
    return _parse_from_binary_dump(data)


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: python parse.py <file_path>')
        sys.exit(1)
    file_path = sys.argv[1]
    items = parse(file_path)
    for i, item in enumerate(items):
        # dump index and hex value
        print('{:04d}: 0x{:08X}'.format(i, item))