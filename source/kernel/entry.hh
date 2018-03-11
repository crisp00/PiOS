/*! \file entry.hh
    \brief mask to the kernel low level functions.
 */

/*! \brief Descriptor structure of Interrupt Descriptor Table

    Adressing is of type GDTSelector:Offset
 */
struct IDTDescr {
   uint16_t offset_1; /**< \brief Bits 0 to 15 of Offset */
   uint16_t selector; /**< \brief Code segment selector in GDT or LDT (GDTSelector) */
   uint8_t zero;      /**< \brief Unused, set to 0 */
   uint8_t type_attr; /**< \brief Type and attributes */
   uint16_t offset_2; /**< \brief Bits 16 to 31 of Offset */
} typedef IDTDescr_t;

extern IDTDescr_t PIOS_IDT[256]; /**< \brief Pointer to IDT */

extern uint32_t INT0; 
extern uint32_t INT1;
extern uint32_t INT2;
extern uint32_t INT3;
extern uint32_t INT4;
extern uint32_t INT5;
extern uint32_t INT6;
extern uint32_t INT7;
extern uint32_t INT8;
extern uint32_t INT9;
extern uint32_t INT10;
extern uint32_t INT11;
extern uint32_t INT12;
extern uint32_t INT13;
extern uint32_t INT14;
extern uint32_t INT15;
extern uint32_t INT16;
extern uint32_t INT17;
extern uint32_t INT18;
extern uint32_t INT19;
extern uint32_t INT20;
extern uint32_t INT21;
extern uint32_t INT22;
extern uint32_t INT23;
extern uint32_t INT24;
extern uint32_t INT25;
extern uint32_t INT26;
extern uint32_t INT27;
extern uint32_t INT28;
extern uint32_t INT29;
extern uint32_t INT30;
extern uint32_t INT31;
extern uint32_t INT32;
extern uint32_t INT33;
extern uint32_t INT34;
extern uint32_t INT35;
extern uint32_t INT36;
extern uint32_t INT37;
extern uint32_t INT38;
extern uint32_t INT39;
extern uint32_t INT40;
extern uint32_t INT41;
extern uint32_t INT42;
extern uint32_t INT43;
extern uint32_t INT44;
extern uint32_t INT45;
extern uint32_t INT46;
extern uint32_t INT47;
extern uint32_t INT48;
extern uint32_t INT49;
extern uint32_t INT50;
extern uint32_t INT51;
extern uint32_t INT52;
extern uint32_t INT53;
extern uint32_t INT54;
extern uint32_t INT55;
extern uint32_t INT56;
extern uint32_t INT57;
extern uint32_t INT58;
extern uint32_t INT59;
extern uint32_t INT60;
extern uint32_t INT61;
extern uint32_t INT62;
extern uint32_t INT63;
extern uint32_t INT64;
extern uint32_t INT65;
extern uint32_t INT66;
extern uint32_t INT67;
extern uint32_t INT68;
extern uint32_t INT69;
extern uint32_t INT70;
extern uint32_t INT71;
extern uint32_t INT72;
extern uint32_t INT73;
extern uint32_t INT74;
extern uint32_t INT75;
extern uint32_t INT76;
extern uint32_t INT77;
extern uint32_t INT78;
extern uint32_t INT79;
extern uint32_t INT80;
extern uint32_t INT81;
extern uint32_t INT82;
extern uint32_t INT83;
extern uint32_t INT84;
extern uint32_t INT85;
extern uint32_t INT86;
extern uint32_t INT87;
extern uint32_t INT88;
extern uint32_t INT89;
extern uint32_t INT90;
extern uint32_t INT91;
extern uint32_t INT92;
extern uint32_t INT93;
extern uint32_t INT94;
extern uint32_t INT95;
extern uint32_t INT96;
extern uint32_t INT97;
extern uint32_t INT98;
extern uint32_t INT99;
extern uint32_t INT100;
extern uint32_t INT101;
extern uint32_t INT102;
extern uint32_t INT103;
extern uint32_t INT104;
extern uint32_t INT105;
extern uint32_t INT106;
extern uint32_t INT107;
extern uint32_t INT108;
extern uint32_t INT109;
extern uint32_t INT110;
extern uint32_t INT111;
extern uint32_t INT112;
extern uint32_t INT113;
extern uint32_t INT114;
extern uint32_t INT115;
extern uint32_t INT116;
extern uint32_t INT117;
extern uint32_t INT118;
extern uint32_t INT119;
extern uint32_t INT120;
extern uint32_t INT121;
extern uint32_t INT122;
extern uint32_t INT123;
extern uint32_t INT124;
extern uint32_t INT125;
extern uint32_t INT126;
extern uint32_t INT127;
extern uint32_t INT128;
extern uint32_t INT129;
extern uint32_t INT130;
extern uint32_t INT131;
extern uint32_t INT132;
extern uint32_t INT133;
extern uint32_t INT134;
extern uint32_t INT135;
extern uint32_t INT136;
extern uint32_t INT137;
extern uint32_t INT138;
extern uint32_t INT139;
extern uint32_t INT140;
extern uint32_t INT141;
extern uint32_t INT142;
extern uint32_t INT143;
extern uint32_t INT144;
extern uint32_t INT145;
extern uint32_t INT146;
extern uint32_t INT147;
extern uint32_t INT148;
extern uint32_t INT149;
extern uint32_t INT150;
extern uint32_t INT151;
extern uint32_t INT152;
extern uint32_t INT153;
extern uint32_t INT154;
extern uint32_t INT155;
extern uint32_t INT156;
extern uint32_t INT157;
extern uint32_t INT158;
extern uint32_t INT159;
extern uint32_t INT160;
extern uint32_t INT161;
extern uint32_t INT162;
extern uint32_t INT163;
extern uint32_t INT164;
extern uint32_t INT165;
extern uint32_t INT166;
extern uint32_t INT167;
extern uint32_t INT168;
extern uint32_t INT169;
extern uint32_t INT170;
extern uint32_t INT171;
extern uint32_t INT172;
extern uint32_t INT173;
extern uint32_t INT174;
extern uint32_t INT175;
extern uint32_t INT176;
extern uint32_t INT177;
extern uint32_t INT178;
extern uint32_t INT179;
extern uint32_t INT180;
extern uint32_t INT181;
extern uint32_t INT182;
extern uint32_t INT183;
extern uint32_t INT184;
extern uint32_t INT185;
extern uint32_t INT186;
extern uint32_t INT187;
extern uint32_t INT188;
extern uint32_t INT189;
extern uint32_t INT190;
extern uint32_t INT191;
extern uint32_t INT192;
extern uint32_t INT193;
extern uint32_t INT194;
extern uint32_t INT195;
extern uint32_t INT196;
extern uint32_t INT197;
extern uint32_t INT198;
extern uint32_t INT199;
extern uint32_t INT200;
extern uint32_t INT201;
extern uint32_t INT202;
extern uint32_t INT203;
extern uint32_t INT204;
extern uint32_t INT205;
extern uint32_t INT206;
extern uint32_t INT207;
extern uint32_t INT208;
extern uint32_t INT209;
extern uint32_t INT210;
extern uint32_t INT211;
extern uint32_t INT212;
extern uint32_t INT213;
extern uint32_t INT214;
extern uint32_t INT215;
extern uint32_t INT216;
extern uint32_t INT217;
extern uint32_t INT218;
extern uint32_t INT219;
extern uint32_t INT220;
extern uint32_t INT221;
extern uint32_t INT222;
extern uint32_t INT223;
extern uint32_t INT224;
extern uint32_t INT225;
extern uint32_t INT226;
extern uint32_t INT227;
extern uint32_t INT228;
extern uint32_t INT229;
extern uint32_t INT230;
extern uint32_t INT231;
extern uint32_t INT232;
extern uint32_t INT233;
extern uint32_t INT234;
extern uint32_t INT235;
extern uint32_t INT236;
extern uint32_t INT237;
extern uint32_t INT238;
extern uint32_t INT239;
extern uint32_t INT240;
extern uint32_t INT241;
extern uint32_t INT242;
extern uint32_t INT243;
extern uint32_t INT244;
extern uint32_t INT245;
extern uint32_t INT246;
extern uint32_t INT247;
extern uint32_t INT248;
extern uint32_t INT249;
extern uint32_t INT250;
extern uint32_t INT251;
extern uint32_t INT252;
extern uint32_t INT253;
extern uint32_t INT254;
extern uint32_t INT255;