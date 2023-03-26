#include <stdio.h>

int maxDescendingSequence(int arr[], int size) {
    int maxLength = 1; // comprimento máximo da sequência
    int currentLength = 1; // comprimento atual da sequência
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i-1]) {
            currentLength++;
            if (currentLength > maxLength) {
                maxLength = currentLength;
            }
        } else {
            currentLength = 1;
        }
    }
    return maxLength;
}

int main() {
    int arr[1024] = {1500, 6933, 1010, 5397, 6891, 63, 5541, 100, 1799, 7450, 688, 7600, 3071, 3750, 8145, 7595, 8674, 475, 55, 7389, 4779, 6963, 3136, 438, 7858, 9337, 2194, 5483, 5130, 3936, 6437, 6252, 485, 136, 8640, 7330, 9056, 4722, 2908, 7507, 1752, 3377, 9988, 1070, 2948, 1566, 8409, 1826, 1731, 196, 7929, 9345, 5589, 7426, 9947, 9110, 8306, 3738, 8757, 8388, 9263, 9014, 6176, 1080, 8004, 2894, 6846, 4574, 12, 2592, 6830, 3107, 5379, 4610, 9676, 7163, 8847, 5448, 7414, 9255, 3824, 4414, 9554, 5849, 5835, 6597, 4570, 3318, 4415, 6415, 794, 4864, 8895, 7855, 3902, 4778, 3459, 1798, 1442, 1220, 793, 1595, 1906, 6862, 5914, 5792, 3347, 7460, 3647, 63, 7462, 9570, 4819, 4261, 6013, 9379, 9982, 6558, 7819, 8853, 2858, 1026, 3872, 9540, 858, 9402, 2166, 7625, 8379, 6536, 6832, 7275, 2251, 673, 9507, 3132, 8938, 6925, 2013, 832, 8166, 815, 3587, 2371, 6536, 5314, 1421, 8129, 5518, 2841, 2887, 8018, 7301, 522, 5176, 1142, 1665, 4281, 7734, 968, 1159, 1570, 1779, 2318, 5033, 9181, 5729, 7840, 8118, 3914, 1576, 751, 2788, 1675, 2620, 48, 7527, 987, 8942, 2554, 1883, 7780, 3991, 1542, 2373, 5216, 5458, 6537, 3522, 2112, 3367, 3579, 8768, 3296, 7579, 6097, 4524, 187, 7790, 602, 8164, 5103, 3200, 2013, 9344, 5438, 8467, 460, 6346, 64, 470, 5739, 6614, 8203, 7663, 4116, 9047, 969, 1880, 9275, 689, 4308, 5690, 1446, 8884, 6253, 5198, 2002, 9969, 3270, 5875, 781, 7290, 6648, 8002, 6151, 5486, 9467, 537, 9498, 6358, 9411, 9021, 5393, 9683, 7209, 7635, 8288, 9192, 9263, 9834, 9271, 2735, 3563, 884, 4682, 2063, 838, 6864, 7234, 3562, 2289, 4937, 6547, 158, 3036, 6279, 1152, 6242, 9926, 6393, 6795, 9962, 7695, 6723, 3484, 4431, 913, 9955, 1595, 9865, 4380, 3655, 2695, 6907, 4326, 8069, 9512, 6207, 4374, 8001, 5596, 4540, 2925, 8888, 2002, 379, 5715, 9955, 8234, 3058, 5452, 6046, 5190, 4313, 5563, 745, 1286, 4185, 6317, 1291, 5698, 7111, 4063, 1663, 7105, 7516, 4013, 8622, 4433, 966, 2184, 3972, 9808, 1585, 7550, 5, 413, 1677, 6635, 7107, 8683, 2548, 8088, 235, 4955, 5719, 4115, 2793, 2546, 9991, 1547, 7348, 4366, 8990, 4802, 9287, 5482, 7145, 2665, 5712, 190, 5889, 6024, 3541, 850, 1475, 7677, 9297, 3607, 8530, 7019, 768, 1455, 8659, 1857, 5942, 657, 5456, 2012, 7657, 3099, 2123, 2671, 4311, 1548, 6093, 1246, 1051, 8663, 6413, 4562, 7992, 9331, 3970, 518, 5381, 773, 5544, 3117, 5929, 7648, 6616, 1425, 6989, 4824, 807, 631, 124, 7908, 7626, 864, 1016, 5897, 9445, 1927, 3727, 8446, 2047, 6339, 8656, 5566, 7445, 2183, 1724, 5636, 6782, 4918, 4977, 7534, 6085, 333, 9572, 6534, 5898, 480, 1929, 5877, 8938, 2184, 9331, 9111, 7985, 5673, 6646, 5455, 6034, 8762, 5331, 2025, 3522, 9820, 6789, 9166, 2528, 3942, 9624, 1194, 6332, 5696, 7200, 9724, 3112, 7237, 4103, 8243, 9837, 4896, 3807, 3925, 3014, 9224, 1823, 8969, 841, 9919, 5310, 1152, 5455, 1442, 1797, 4030, 6108, 1826, 1022, 1612, 5198, 9077, 6293, 8735, 6670, 7896, 1958, 2217, 6018, 4218, 3270, 8348, 9880, 8826, 9679, 3375, 2861, 8111, 4409, 7059, 6858, 638, 5070, 1639, 5286, 9484, 1319, 5686, 5251, 1626, 4945, 3563, 6973, 1869, 7037, 42, 8219, 5128, 2216, 3014, 3679, 6525, 5304, 2868, 7911, 1007, 4157, 3261, 6696, 9746, 9350, 5405, 6422, 6869, 9094, 6968, 627, 4717, 9268, 4386, 2480, 4563, 9477, 9397, 8041, 1879, 4395, 201, 2245, 1782, 389, 819, 9366, 2845, 6789, 6523, 1815, 223, 226, 5, 7694, 6174, 4662, 9761, 1928, 9867, 571, 877, 1908, 3088, 5081, 9402, 4461, 8977, 2057, 3624, 6252, 5880, 3887, 532, 2010, 7508, 3828, 180, 8642, 28, 4343, 3779, 1041, 9834, 9211, 1692, 6461, 3388, 9889, 1629, 8791, 6056, 3589, 8084, 3701, 6445, 7398, 2178, 6494, 6475, 5545, 509, 6196, 1765, 1183, 8087, 1889, 3082, 9512, 9684, 8962, 1885, 8000, 9147, 8168, 6031, 8755, 8711, 9232, 5290, 6612, 4387, 666, 5945, 3413, 8321, 4165, 963, 4468, 3507, 9296, 724, 2502, 5899, 5392, 5096, 8110, 6427, 7146, 448, 9342, 3066, 7821, 1384, 6531, 6063, 4925, 2434, 2316, 351, 230, 4823, 2740, 9724, 9528, 8252, 6215, 7323, 8199, 5491, 2228, 587, 1387, 5374, 9814, 6253, 191, 3335, 8063, 8129, 802, 4472, 1791, 1028, 8490, 2627, 1387, 9107, 3057, 8076, 3502, 3855, 7366, 4859, 1438, 1900, 6402, 2688, 768, 813, 484, 7007, 3651, 340, 2949, 6692, 5344, 825, 85, 2840, 6962, 9143, 7261, 5780, 3245, 3791, 7051, 7941, 1977, 1245, 7818, 6870, 7281, 437, 5582, 6342, 3512, 4443, 1807, 2346, 1427, 3534, 6282, 7284, 2442, 6961, 5622, 3709, 4437, 1018, 9679, 1532, 3201, 202, 5506, 4025, 7194, 7561, 8178, 1315, 4574, 736, 955, 8122, 9011, 9189, 8780, 8786, 1448, 9182, 402, 8091, 2378, 3829, 1410, 5257, 2236, 572, 5223, 1409, 6320, 7696, 7657, 595, 5432, 1920, 4982, 4989, 9308, 103, 7172, 7368, 7324, 9437, 9600, 3180, 8730, 4086, 1590, 9593, 1918, 917, 1029, 3513, 4034, 4099, 795, 7671, 4419, 4030, 4436, 9721, 3897, 7680, 5373, 63, 3326, 8118, 8701, 4002, 9318, 3618, 3507, 8418, 1671, 3785, 9489, 2033, 2929, 8821, 1188, 6508, 8691, 7094, 6618, 2716, 7521, 7003, 5375, 3381, 3313, 5837, 3844, 48, 5851, 7267, 665, 3384, 7621, 3547, 2366, 3479, 8221, 540, 4147, 7783, 3870, 8723, 6051, 2464, 1481, 7543, 3091, 3141, 1730, 6597, 6296, 7383, 2902, 9864, 7390, 2629, 8317, 9888, 3043, 875, 5457, 8299, 1607, 7346, 8071, 8305, 8820, 5655, 9642, 3503, 6725, 8638, 2992, 7557, 5215, 9125, 7628, 8140, 6788, 2590, 8560, 1146, 2134, 4964, 6566, 296, 6950, 8917, 9832, 7865, 3527, 8176, 8726, 5662, 3037, 7302, 4803, 9172, 8762, 5019, 7893, 4306, 7598, 3054, 2966, 1200, 9223, 5603, 5311, 5561, 7704, 1438, 287, 8776, 8342, 4244, 8087, 9880, 9383, 5465, 7083, 3643, 6479, 2941, 9540, 9832, 716, 8852, 9256, 3706, 8261, 3500, 8061, 4153, 1225, 4557, 2256, 258, 7222, 4846, 409, 8714, 693, 6778, 8291, 135, 8596, 9947, 3371, 1782, 8927, 2190, 6993, 6729, 3909, 8696, 3558, 647, 2872, 3079, 1402, 3680, 7925, 9944, 9891, 8595, 4843, 6133, 6967, 8534, 7359, 70, 8147, 355, 9035, 6027, 9850, 8771, 1155, 4919, 8879, 1721, 6463, 7715, 9489, 8071, 2491, 5221, 5533, 46, 4999, 3574, 5674, 3835, 1313, 3540, 3120, 6971, 6652, 2212, 4933, 9059, 8387, 2611, 4886, 1596, 1649, 9804, 9440, 828, 7419, 6522, 9922, 6639, 5841, 1905, 9762, 2974, 7075, 5963, 41, 6457, 7725, 6856, 774, 8231};



    int size = sizeof(arr) / sizeof(arr[0]);
    int maxLength = maxDescendingSequence(arr, size);
    printf("O comprimento da maior sequência estritamente decrescente no array é: %d", maxLength);
    return 0;
}