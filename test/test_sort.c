#include <stdio.h>

#include "utils.h"

int array[] = {
    93,  382, 943, 396, 490, 94,  897, 276, 858, 57,  602, 516, 878, 258, 834,
    268, 484, 553, 832, 706, 313, 490, 694, 809, 612, 539, 620, 598, 250, 943,
    280, 44,  512, 520, 857, 391, 375, 252, 636, 932, 581, 482, 298, 243, 159,
    633, 403, 349, 161, 19,  171, 908, 643, 752, 548, 33,  899, 758, 120, 214,
    472, 946, 832, 84,  362, 84,  993, 818, 163, 813, 712, 434, 921, 105, 890,
    50,  713, 216, 574, 814, 691, 452, 198, 472, 513, 644, 325, 953, 477, 801,
    758, 289, 156, 343, 139, 359, 540, 297, 193, 251, 267, 850, 309, 542, 31,
    920, 752, 506, 915, 209, 653, 106, 754, 408, 740, 309, 15,  488, 413, 766,
    565, 566, 420, 970, 796, 134, 52,  750, 439, 69,  810, 24,  837, 787, 729,
    506, 347, 738, 777, 360, 659, 213, 271, 595, 311, 411, 471, 203, 878, 629,
    870, 379, 819, 466, 684, 906, 474, 383, 217, 875, 666, 810, 105, 764, 370,
    935, 820, 282, 734, 408, 888, 12,  643, 900, 788, 456, 333, 934, 371, 29,
    989, 715, 180, 322, 121, 795, 124, 335, 57,  250, 823, 96,  212, 626, 481,
    285, 828, 669, 858, 733, 333, 232, 572, 30,  34,  167, 388, 187, 567, 246,
    35,  352, 385, 824, 367, 627, 533, 596, 344, 664, 386, 280, 82,  482, 572,
    109, 346, 456, 454, 467, 126, 640, 956, 84,  615, 863, 196, 611, 910, 253,
    247, 233, 287, 697, 728, 35,  434, 826, 967, 498, 839, 634, 965, 931, 558,
    508, 225, 375, 823, 625, 311, 593, 181, 393, 636, 48,  134, 484, 188, 624,
    602, 616, 465, 430, 166, 231, 453, 937, 903, 794, 841, 1,   320, 567, 64,
    795, 273, 325, 196, 770, 32,  566, 642, 443, 532, 898, 267, 583, 360, 94,
    916, 75,  342, 984, 917, 605, 154, 909, 196, 533, 107, 750, 621, 5,   678,
    290, 61,  516, 433, 60,  191, 406, 769, 526, 164, 834, 678, 261, 393, 561,
    456, 166, 137, 697, 253, 803, 588, 555, 109, 101, 296, 391, 577, 797, 249,
    641, 346, 733, 105, 194, 963, 117, 437, 458, 760, 770, 94,  319, 921, 607,
    601, 599, 160, 116, 139, 530, 831, 797, 486, 60,  514, 999, 317, 324, 348,
    243, 149, 617, 494, 294, 387, 622, 406, 41,  211, 620, 657, 783, 898, 630,
    507, 371, 70,  76,  139, 213, 359, 412, 113, 357, 562, 409, 485, 703, 437,
    242, 469, 857, 120, 227, 714, 771, 434, 19,  315, 305, 899, 474, 889, 352,
    760, 523, 140, 21,  96,  996, 937, 228, 711, 451, 625, 405, 322, 849, 836,
    859, 401, 831, 864, 918, 387, 947, 927, 355, 181, 871, 584, 520, 785, 408,
    173, 563, 397, 379, 285, 441, 739, 731, 950, 328, 416, 382, 563, 106, 103,
    889, 480, 314, 471, 325, 392, 438, 512, 581, 40,  98,  781, 714, 449, 803,
    594, 294, 939, 496, 763, 266, 96,  630, 874, 846, 809, 280, 122, 276, 526,
    104, 144, 9,   878, 245, 729, 661, 219, 202, 406, 975, 753, 27,  106, 637,
    315, 969, 22,  234, 104, 307, 972, 705, 667, 456, 391, 472, 760, 707, 177,
    592, 623, 271, 142, 957, 247, 463, 591, 238, 176, 886, 804, 547, 893, 888,
    121, 350, 868, 776, 95,  950, 371, 392, 796, 40,  317, 689, 245, 237, 994,
    92,  190, 393, 618, 450, 306, 166, 983, 872, 375, 380, 179, 826, 93,  136,
    183, 958, 243, 285, 501, 672, 806, 898, 197, 922, 174, 750, 602, 472, 649,
    419, 321, 834, 46,  937, 662, 635, 884, 587, 801, 4,   595, 187, 46,  983,
    787, 962, 116, 638, 919, 318, 810, 236, 350, 990, 794, 828, 544, 456, 329,
    468, 668, 580, 302, 25,  181, 291, 900, 689, 625, 204, 759, 99,  718, 12,
    361, 451, 286, 845, 287, 739, 103, 625, 404, 591, 41,  824, 50,  265, 494,
    65,  348, 948, 53,  483, 31,  46,  67,  598, 116, 931, 145, 887, 582, 571,
    842, 520, 419, 816, 559, 657, 992, 844, 382, 978, 444, 815, 625, 200, 130,
    317, 659, 709, 970, 565, 153, 678, 787, 212, 947, 582, 944, 872, 409, 792,
    328, 10,  844, 792, 158, 770, 290, 645, 792, 807, 504, 7,   50,  267, 342,
    902, 39,  382, 834, 808, 375, 857, 905, 323, 231, 387, 112, 117, 130, 202,
    72,  859, 813, 46,  252, 92,  278, 203, 624, 404, 485, 965, 681, 230, 441,
    390, 851, 120, 753, 609, 708, 67,  520, 944, 205, 815, 996, 164, 841, 372,
    335, 457, 370, 123, 227, 368, 145, 364, 890, 916, 673, 516, 760, 947, 409,
    952, 329, 669, 656, 530, 336, 525, 881, 872, 742, 984, 562, 544, 165, 449,
    567, 690, 739, 684, 764, 749, 630, 731, 682, 252, 143, 745, 931, 32,  872,
    381, 302, 825, 72,  117, 527, 303, 476, 937, 120, 628, 40,  618, 188, 427,
    847, 552, 663, 148, 776, 777, 238, 998, 179, 98,  299, 953, 110, 511, 751,
    503, 432, 484, 381, 272, 546, 113, 874, 829, 175, 51,  969, 131, 268, 127,
    326, 660, 714, 793, 293, 968, 340, 472, 537, 132, 217, 562, 678, 230, 879,
    223, 777, 997, 201, 839, 308, 289, 253, 243, 833, 170, 421, 948, 318, 69,
    220, 866, 883, 871, 521, 311, 478, 539, 800, 634, 224, 352, 267, 694, 745,
    298, 158, 856, 550, 47,  963, 40,  633, 47,  500, 170, 828, 766, 2,   301,
    453, 289, 103, 621, 577, 556, 222, 238, 615, 843, 324, 727, 781, 266, 875,
    236, 374, 281, 961, 706, 748, 909, 740, 540, 967, 257, 645, 945, 303, 954,
    642, 470, 208, 983, 527, 61,  464, 372, 740, 615, 887, 57,  811, 574, 299,
    25,  851, 377, 105, 203, 484, 558, 257, 68,  866, 907, 799, 594, 713, 568,
    997, 234, 30,  223, 333, 144, 91,  14,  91,  408, 434, 328, 663, 644, 304,
    361, 272, 970, 310, 232, 209, 176, 34,  895, 173, 838, 543, 317, 984, 336,
    859, 953, 577, 653, 96,  99,  671, 125, 565, 938
};

int main(void) {
  sort(array, 1000);
  for (int i = 0; i < 1000; i++) {
    printf("%3d%s", array[i], i == 999 ? "\n" : ", ");
  }

  return 0;
}