#include "MenusEntries.h"

std::map<String, Bitmap> imageMap = {
    {"whale", {64, 42, image_whale_copy_bits}},
    {"frame_not_selected", {124, 20, image_frame_not_selected_bits}},
    {"frame_selected", {124, 20, image_frame_selected_bits}},
    {"folder_open_file", {18, 14, image_folder_open_file_bits}},
    {"music_radio_streaming", {17, 16, image_music_radio_streaming_bits}},
    {"pencil", {14, 14, image_pencil_bits}},
    {"nfc", {18, 10, image_nfc_bits}},
    {"rfid", {23, 10, image_rfid_bits}},
    {"arrow_curved_right_up_down", {7, 5, image_arrow_curved_right_up_down_bits}},
    {"arrow_right", {9, 7, image_arrow_right_bits}},
    {"heading_frame", {61, 11, image_heading_frame_bits}}
};

std::map<Menu, std::vector<String>> menuItems = {
    {MAIN, {"Wallet", "Read", "Write"}},
    {READ_FREQUENCIES, {"13.56MHz", "125KHz", "Dual-freq"}},
    {NFC_READ_OPTIONS, {"Read blocks", "Save UID only", "Read Ndef message"}},
    {CRACK_KEY, {"Crack the key", "Insert the key"}}
};

std::map<String, String> iconMap = {
    {"Wallet", "folder_open_file"},
    {"Read", "music_radio_streaming"},
    {"Write", "pencil"},
    {"13.56MHz", "nfc"},
    {"125KHz", "rfid"},
    {"Dual-frequencies", "music_radio_streaming"}
};