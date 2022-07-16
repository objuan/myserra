/**
 * @file       BlynkHandlers.cpp
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief      Virtual pin utilities
 */

#include <Blynk/BlynkConfig.h>
#include "VHandlers.h"
#include "config.h"
//#include <Blynk/BlynkDebug.h>


void VirtualNoOpCbk()
{}

void VirtualRead(VirtualReq VIRTUAL_UNUSED &request)
{

    Warn("No handler for reading from pin ", request.pin);
}

void VirtualWrite(VirtualReq VIRTUAL_UNUSED &request, const BlynkParam VIRTUAL_UNUSED &param)
{
    //Warn("No handler for writing to pin ", request.pin);
    Serial.println("ll");
}

#define VIRTUAL_ON_READ_IMPL(pin)  void VirtualRead  ## pin (VirtualReq VIRTUAL_UNUSED &req) \
          __attribute__((weak, alias("VirtualRead")))

#define VIRTUAL_ON_WRITE_IMPL(pin) void VirtualWrite ## pin (VirtualReq VIRTUAL_UNUSED &req, const BlynkParam VIRTUAL_UNUSED &param) \
          __attribute__((weak, alias("VirtualWrite")))

VIRTUAL_CONNECTED() __attribute__((weak, alias("VirtualNoOpCbk")));
VIRTUAL_DISCONNECTED() __attribute__((weak, alias("VirtualNoOpCbk")));

// Internal Virtual Pins
VIRTUAL_ON_WRITE_IMPL(InternalPinACON);
VIRTUAL_ON_WRITE_IMPL(InternalPinADIS);
VIRTUAL_ON_WRITE_IMPL(InternalPinRTC);
VIRTUAL_ON_WRITE_IMPL(InternalPinUTC);
VIRTUAL_ON_WRITE_IMPL(InternalPinOTA);
VIRTUAL_ON_WRITE_IMPL(InternalPinMETA);

// Regular Virtual Pins
VIRTUAL_ON_READ_IMPL(Default);
VIRTUAL_ON_WRITE_IMPL(Default);

VIRTUAL_ON_READ_IMPL(0 );
VIRTUAL_ON_READ_IMPL(1 );
VIRTUAL_ON_READ_IMPL(2 );
VIRTUAL_ON_READ_IMPL(3 );
VIRTUAL_ON_READ_IMPL(4 );
VIRTUAL_ON_READ_IMPL(5 );
VIRTUAL_ON_READ_IMPL(6 );
VIRTUAL_ON_READ_IMPL(7 );
VIRTUAL_ON_READ_IMPL(8 );
VIRTUAL_ON_READ_IMPL(9 );
VIRTUAL_ON_READ_IMPL(10);
VIRTUAL_ON_READ_IMPL(11);
VIRTUAL_ON_READ_IMPL(12);
VIRTUAL_ON_READ_IMPL(13);
VIRTUAL_ON_READ_IMPL(14);
VIRTUAL_ON_READ_IMPL(15);
VIRTUAL_ON_READ_IMPL(16);
VIRTUAL_ON_READ_IMPL(17);
VIRTUAL_ON_READ_IMPL(18);
VIRTUAL_ON_READ_IMPL(19);
VIRTUAL_ON_READ_IMPL(20);
VIRTUAL_ON_READ_IMPL(21);
VIRTUAL_ON_READ_IMPL(22);
VIRTUAL_ON_READ_IMPL(23);
VIRTUAL_ON_READ_IMPL(24);
VIRTUAL_ON_READ_IMPL(25);
VIRTUAL_ON_READ_IMPL(26);
VIRTUAL_ON_READ_IMPL(27);
VIRTUAL_ON_READ_IMPL(28);
VIRTUAL_ON_READ_IMPL(29);
VIRTUAL_ON_READ_IMPL(30);
VIRTUAL_ON_READ_IMPL(31);

  VIRTUAL_ON_READ_IMPL(32);
  VIRTUAL_ON_READ_IMPL(33);
  VIRTUAL_ON_READ_IMPL(34);
  VIRTUAL_ON_READ_IMPL(35);
  VIRTUAL_ON_READ_IMPL(36);
  VIRTUAL_ON_READ_IMPL(37);
  VIRTUAL_ON_READ_IMPL(38);
  VIRTUAL_ON_READ_IMPL(39);
  VIRTUAL_ON_READ_IMPL(40);
  VIRTUAL_ON_READ_IMPL(41);
  VIRTUAL_ON_READ_IMPL(42);
  VIRTUAL_ON_READ_IMPL(43);
  VIRTUAL_ON_READ_IMPL(44);
  VIRTUAL_ON_READ_IMPL(45);
  VIRTUAL_ON_READ_IMPL(46);
  VIRTUAL_ON_READ_IMPL(47);
  VIRTUAL_ON_READ_IMPL(48);
  VIRTUAL_ON_READ_IMPL(49);
  VIRTUAL_ON_READ_IMPL(50);
  VIRTUAL_ON_READ_IMPL(51);
  VIRTUAL_ON_READ_IMPL(52);
  VIRTUAL_ON_READ_IMPL(53);
  VIRTUAL_ON_READ_IMPL(54);
  VIRTUAL_ON_READ_IMPL(55);
  VIRTUAL_ON_READ_IMPL(56);
  VIRTUAL_ON_READ_IMPL(57);
  VIRTUAL_ON_READ_IMPL(58);
  VIRTUAL_ON_READ_IMPL(59);
  VIRTUAL_ON_READ_IMPL(60);
  VIRTUAL_ON_READ_IMPL(61);
  VIRTUAL_ON_READ_IMPL(62);
  VIRTUAL_ON_READ_IMPL(63);
  VIRTUAL_ON_READ_IMPL(64);
  VIRTUAL_ON_READ_IMPL(65);
  VIRTUAL_ON_READ_IMPL(66);
  VIRTUAL_ON_READ_IMPL(67);
  VIRTUAL_ON_READ_IMPL(68);
  VIRTUAL_ON_READ_IMPL(69);
  VIRTUAL_ON_READ_IMPL(70);
  VIRTUAL_ON_READ_IMPL(71);
  VIRTUAL_ON_READ_IMPL(72);
  VIRTUAL_ON_READ_IMPL(73);
  VIRTUAL_ON_READ_IMPL(74);
  VIRTUAL_ON_READ_IMPL(75);
  VIRTUAL_ON_READ_IMPL(76);
  VIRTUAL_ON_READ_IMPL(77);
  VIRTUAL_ON_READ_IMPL(78);
  VIRTUAL_ON_READ_IMPL(79);
  VIRTUAL_ON_READ_IMPL(80);
  VIRTUAL_ON_READ_IMPL(81);
  VIRTUAL_ON_READ_IMPL(82);
  VIRTUAL_ON_READ_IMPL(83);
  VIRTUAL_ON_READ_IMPL(84);
  VIRTUAL_ON_READ_IMPL(85);
  VIRTUAL_ON_READ_IMPL(86);
  VIRTUAL_ON_READ_IMPL(87);
  VIRTUAL_ON_READ_IMPL(88);
  VIRTUAL_ON_READ_IMPL(89);
  VIRTUAL_ON_READ_IMPL(90);
  VIRTUAL_ON_READ_IMPL(91);
  VIRTUAL_ON_READ_IMPL(92);
  VIRTUAL_ON_READ_IMPL(93);
  VIRTUAL_ON_READ_IMPL(94);
  VIRTUAL_ON_READ_IMPL(95);
  VIRTUAL_ON_READ_IMPL(96);
  VIRTUAL_ON_READ_IMPL(97);
  VIRTUAL_ON_READ_IMPL(98);
  VIRTUAL_ON_READ_IMPL(99);
  VIRTUAL_ON_READ_IMPL(100);
  VIRTUAL_ON_READ_IMPL(101);
  VIRTUAL_ON_READ_IMPL(102);
  VIRTUAL_ON_READ_IMPL(103);
  VIRTUAL_ON_READ_IMPL(104);
  VIRTUAL_ON_READ_IMPL(105);
  VIRTUAL_ON_READ_IMPL(106);
  VIRTUAL_ON_READ_IMPL(107);
  VIRTUAL_ON_READ_IMPL(108);
  VIRTUAL_ON_READ_IMPL(109);
  VIRTUAL_ON_READ_IMPL(110);
  VIRTUAL_ON_READ_IMPL(111);
  VIRTUAL_ON_READ_IMPL(112);
  VIRTUAL_ON_READ_IMPL(113);
  VIRTUAL_ON_READ_IMPL(114);
  VIRTUAL_ON_READ_IMPL(115);
  VIRTUAL_ON_READ_IMPL(116);
  VIRTUAL_ON_READ_IMPL(117);
  VIRTUAL_ON_READ_IMPL(118);
  VIRTUAL_ON_READ_IMPL(119);
  VIRTUAL_ON_READ_IMPL(120);
  VIRTUAL_ON_READ_IMPL(121);
  VIRTUAL_ON_READ_IMPL(122);
  VIRTUAL_ON_READ_IMPL(123);
  VIRTUAL_ON_READ_IMPL(124);
  VIRTUAL_ON_READ_IMPL(125);
  VIRTUAL_ON_READ_IMPL(126);
  VIRTUAL_ON_READ_IMPL(127);


VIRTUAL_ON_WRITE_IMPL(0 );
VIRTUAL_ON_WRITE_IMPL(1 );
VIRTUAL_ON_WRITE_IMPL(2 );
VIRTUAL_ON_WRITE_IMPL(3 );
VIRTUAL_ON_WRITE_IMPL(4 );
VIRTUAL_ON_WRITE_IMPL(5 );
VIRTUAL_ON_WRITE_IMPL(6 );
VIRTUAL_ON_WRITE_IMPL(7 );
VIRTUAL_ON_WRITE_IMPL(8 );
VIRTUAL_ON_WRITE_IMPL(9 );
VIRTUAL_ON_WRITE_IMPL(10);
VIRTUAL_ON_WRITE_IMPL(11);
VIRTUAL_ON_WRITE_IMPL(12);
VIRTUAL_ON_WRITE_IMPL(13);
VIRTUAL_ON_WRITE_IMPL(14);
VIRTUAL_ON_WRITE_IMPL(15);
VIRTUAL_ON_WRITE_IMPL(16);
VIRTUAL_ON_WRITE_IMPL(17);
VIRTUAL_ON_WRITE_IMPL(18);
VIRTUAL_ON_WRITE_IMPL(19);
VIRTUAL_ON_WRITE_IMPL(20);
VIRTUAL_ON_WRITE_IMPL(21);
VIRTUAL_ON_WRITE_IMPL(22);
VIRTUAL_ON_WRITE_IMPL(23);
VIRTUAL_ON_WRITE_IMPL(24);
VIRTUAL_ON_WRITE_IMPL(25);
VIRTUAL_ON_WRITE_IMPL(26);
VIRTUAL_ON_WRITE_IMPL(27);
VIRTUAL_ON_WRITE_IMPL(28);
VIRTUAL_ON_WRITE_IMPL(29);
VIRTUAL_ON_WRITE_IMPL(30);
VIRTUAL_ON_WRITE_IMPL(31);

  VIRTUAL_ON_WRITE_IMPL(32);
  VIRTUAL_ON_WRITE_IMPL(33);
  VIRTUAL_ON_WRITE_IMPL(34);
  VIRTUAL_ON_WRITE_IMPL(35);
  VIRTUAL_ON_WRITE_IMPL(36);
  VIRTUAL_ON_WRITE_IMPL(37);
  VIRTUAL_ON_WRITE_IMPL(38);
  VIRTUAL_ON_WRITE_IMPL(39);
  VIRTUAL_ON_WRITE_IMPL(40);
  VIRTUAL_ON_WRITE_IMPL(41);
  VIRTUAL_ON_WRITE_IMPL(42);
  VIRTUAL_ON_WRITE_IMPL(43);
  VIRTUAL_ON_WRITE_IMPL(44);
  VIRTUAL_ON_WRITE_IMPL(45);
  VIRTUAL_ON_WRITE_IMPL(46);
  VIRTUAL_ON_WRITE_IMPL(47);
  VIRTUAL_ON_WRITE_IMPL(48);
  VIRTUAL_ON_WRITE_IMPL(49);
  VIRTUAL_ON_WRITE_IMPL(50);
  VIRTUAL_ON_WRITE_IMPL(51);
  VIRTUAL_ON_WRITE_IMPL(52);
  VIRTUAL_ON_WRITE_IMPL(53);
  VIRTUAL_ON_WRITE_IMPL(54);
  VIRTUAL_ON_WRITE_IMPL(55);
  VIRTUAL_ON_WRITE_IMPL(56);
  VIRTUAL_ON_WRITE_IMPL(57);
  VIRTUAL_ON_WRITE_IMPL(58);
  VIRTUAL_ON_WRITE_IMPL(59);
  VIRTUAL_ON_WRITE_IMPL(60);
  VIRTUAL_ON_WRITE_IMPL(61);
  VIRTUAL_ON_WRITE_IMPL(62);
  VIRTUAL_ON_WRITE_IMPL(63);
  VIRTUAL_ON_WRITE_IMPL(64);
  VIRTUAL_ON_WRITE_IMPL(65);
  VIRTUAL_ON_WRITE_IMPL(66);
  VIRTUAL_ON_WRITE_IMPL(67);
  VIRTUAL_ON_WRITE_IMPL(68);
  VIRTUAL_ON_WRITE_IMPL(69);
  VIRTUAL_ON_WRITE_IMPL(70);
  VIRTUAL_ON_WRITE_IMPL(71);
  VIRTUAL_ON_WRITE_IMPL(72);
  VIRTUAL_ON_WRITE_IMPL(73);
  VIRTUAL_ON_WRITE_IMPL(74);
  VIRTUAL_ON_WRITE_IMPL(75);
  VIRTUAL_ON_WRITE_IMPL(76);
  VIRTUAL_ON_WRITE_IMPL(77);
  VIRTUAL_ON_WRITE_IMPL(78);
  VIRTUAL_ON_WRITE_IMPL(79);
  VIRTUAL_ON_WRITE_IMPL(80);
  VIRTUAL_ON_WRITE_IMPL(81);
  VIRTUAL_ON_WRITE_IMPL(82);
  VIRTUAL_ON_WRITE_IMPL(83);
  VIRTUAL_ON_WRITE_IMPL(84);
  VIRTUAL_ON_WRITE_IMPL(85);
  VIRTUAL_ON_WRITE_IMPL(86);
  VIRTUAL_ON_WRITE_IMPL(87);
  VIRTUAL_ON_WRITE_IMPL(88);
  VIRTUAL_ON_WRITE_IMPL(89);
  VIRTUAL_ON_WRITE_IMPL(90);
  VIRTUAL_ON_WRITE_IMPL(91);
  VIRTUAL_ON_WRITE_IMPL(92);
  VIRTUAL_ON_WRITE_IMPL(93);
  VIRTUAL_ON_WRITE_IMPL(94);
  VIRTUAL_ON_WRITE_IMPL(95);
  VIRTUAL_ON_WRITE_IMPL(96);
  VIRTUAL_ON_WRITE_IMPL(97);
  VIRTUAL_ON_WRITE_IMPL(98);
  VIRTUAL_ON_WRITE_IMPL(99);
  VIRTUAL_ON_WRITE_IMPL(100);
  VIRTUAL_ON_WRITE_IMPL(101);
  VIRTUAL_ON_WRITE_IMPL(102);
  VIRTUAL_ON_WRITE_IMPL(103);
  VIRTUAL_ON_WRITE_IMPL(104);
  VIRTUAL_ON_WRITE_IMPL(105);
  VIRTUAL_ON_WRITE_IMPL(106);
  VIRTUAL_ON_WRITE_IMPL(107);
  VIRTUAL_ON_WRITE_IMPL(108);
  VIRTUAL_ON_WRITE_IMPL(109);
  VIRTUAL_ON_WRITE_IMPL(110);
  VIRTUAL_ON_WRITE_IMPL(111);
  VIRTUAL_ON_WRITE_IMPL(112);
  VIRTUAL_ON_WRITE_IMPL(113);
  VIRTUAL_ON_WRITE_IMPL(114);
  VIRTUAL_ON_WRITE_IMPL(115);
  VIRTUAL_ON_WRITE_IMPL(116);
  VIRTUAL_ON_WRITE_IMPL(117);
  VIRTUAL_ON_WRITE_IMPL(118);
  VIRTUAL_ON_WRITE_IMPL(119);
  VIRTUAL_ON_WRITE_IMPL(120);
  VIRTUAL_ON_WRITE_IMPL(121);
  VIRTUAL_ON_WRITE_IMPL(122);
  VIRTUAL_ON_WRITE_IMPL(123);
  VIRTUAL_ON_WRITE_IMPL(124);
  VIRTUAL_ON_WRITE_IMPL(125);
  VIRTUAL_ON_WRITE_IMPL(126);
  VIRTUAL_ON_WRITE_IMPL(127);


static const VirtualReadHandler VirtualReadHandlerVector[]  = {
    VirtualRead0,   VirtualRead1,   VirtualRead2,   VirtualRead3,
    VirtualRead4,   VirtualRead5,   VirtualRead6,   VirtualRead7,
    VirtualRead8,   VirtualRead9,   VirtualRead10,  VirtualRead11,
    VirtualRead12,  VirtualRead13,  VirtualRead14,  VirtualRead15,
    VirtualRead16,  VirtualRead17,  VirtualRead18,  VirtualRead19,
    VirtualRead20,  VirtualRead21,  VirtualRead22,  VirtualRead23,
    VirtualRead24,  VirtualRead25,  VirtualRead26,  VirtualRead27,
    VirtualRead28,  VirtualRead29,  VirtualRead30,  VirtualRead31,

    VirtualRead32,  VirtualRead33,  VirtualRead34,  VirtualRead35,
    VirtualRead36,  VirtualRead37,  VirtualRead38,  VirtualRead39,
    VirtualRead40,  VirtualRead41,  VirtualRead42,  VirtualRead43,
    VirtualRead44,  VirtualRead45,  VirtualRead46,  VirtualRead47,
    VirtualRead48,  VirtualRead49,  VirtualRead50,  VirtualRead51,
    VirtualRead52,  VirtualRead53,  VirtualRead54,  VirtualRead55,
    VirtualRead56,  VirtualRead57,  VirtualRead58,  VirtualRead59,
    VirtualRead60,  VirtualRead61,  VirtualRead62,  VirtualRead63,
    VirtualRead64,  VirtualRead65,  VirtualRead66,  VirtualRead67,
    VirtualRead68,  VirtualRead69,  VirtualRead70,  VirtualRead71,
    VirtualRead72,  VirtualRead73,  VirtualRead74,  VirtualRead75,
    VirtualRead76,  VirtualRead77,  VirtualRead78,  VirtualRead79,
    VirtualRead80,  VirtualRead81,  VirtualRead82,  VirtualRead83,
    VirtualRead84,  VirtualRead85,  VirtualRead86,  VirtualRead87,
    VirtualRead88,  VirtualRead89,  VirtualRead90,  VirtualRead91,
    VirtualRead92,  VirtualRead93,  VirtualRead94,  VirtualRead95,
    VirtualRead96,  VirtualRead97,  VirtualRead98,  VirtualRead99,
    VirtualRead100,  VirtualRead101,  VirtualRead102,  VirtualRead103,
    VirtualRead104,  VirtualRead105,  VirtualRead106,  VirtualRead107,
    VirtualRead108,  VirtualRead109,  VirtualRead110,  VirtualRead111,
    VirtualRead112,  VirtualRead113,  VirtualRead114,  VirtualRead115,
    VirtualRead116,  VirtualRead117,  VirtualRead118,  VirtualRead119,
    VirtualRead120,  VirtualRead121,  VirtualRead122,  VirtualRead123,
    VirtualRead124,  VirtualRead125,  VirtualRead126,  VirtualRead127,

};

static const VirtualWriteHandler VirtualWriteHandlerVector[]  = {
    VirtualWrite0,  VirtualWrite1,  VirtualWrite2,  VirtualWrite3,
    VirtualWrite4,  VirtualWrite5,  VirtualWrite6,  VirtualWrite7,
    VirtualWrite8,  VirtualWrite9,  VirtualWrite10, VirtualWrite11,
    VirtualWrite12, VirtualWrite13, VirtualWrite14, VirtualWrite15,
    VirtualWrite16, VirtualWrite17, VirtualWrite18, VirtualWrite19,
    VirtualWrite20, VirtualWrite21, VirtualWrite22, VirtualWrite23,
    VirtualWrite24, VirtualWrite25, VirtualWrite26, VirtualWrite27,
    VirtualWrite28, VirtualWrite29, VirtualWrite30, VirtualWrite31,

    VirtualWrite32,  VirtualWrite33,  VirtualWrite34,  VirtualWrite35,
    VirtualWrite36,  VirtualWrite37,  VirtualWrite38,  VirtualWrite39,
    VirtualWrite40,  VirtualWrite41,  VirtualWrite42,  VirtualWrite43,
    VirtualWrite44,  VirtualWrite45,  VirtualWrite46,  VirtualWrite47,
    VirtualWrite48,  VirtualWrite49,  VirtualWrite50,  VirtualWrite51,
    VirtualWrite52,  VirtualWrite53,  VirtualWrite54,  VirtualWrite55,
    VirtualWrite56,  VirtualWrite57,  VirtualWrite58,  VirtualWrite59,
    VirtualWrite60,  VirtualWrite61,  VirtualWrite62,  VirtualWrite63,
    VirtualWrite64,  VirtualWrite65,  VirtualWrite66,  VirtualWrite67,
    VirtualWrite68,  VirtualWrite69,  VirtualWrite70,  VirtualWrite71,
    VirtualWrite72,  VirtualWrite73,  VirtualWrite74,  VirtualWrite75,
    VirtualWrite76,  VirtualWrite77,  VirtualWrite78,  VirtualWrite79,
    VirtualWrite80,  VirtualWrite81,  VirtualWrite82,  VirtualWrite83,
    VirtualWrite84,  VirtualWrite85,  VirtualWrite86,  VirtualWrite87,
    VirtualWrite88,  VirtualWrite89,  VirtualWrite90,  VirtualWrite91,
    VirtualWrite92,  VirtualWrite93,  VirtualWrite94,  VirtualWrite95,
    VirtualWrite96,  VirtualWrite97,  VirtualWrite98,  VirtualWrite99,
    VirtualWrite100,  VirtualWrite101,  VirtualWrite102,  VirtualWrite103,
    VirtualWrite104,  VirtualWrite105,  VirtualWrite106,  VirtualWrite107,
    VirtualWrite108,  VirtualWrite109,  VirtualWrite110,  VirtualWrite111,
    VirtualWrite112,  VirtualWrite113,  VirtualWrite114,  VirtualWrite115,
    VirtualWrite116,  VirtualWrite117,  VirtualWrite118,  VirtualWrite119,
    VirtualWrite120,  VirtualWrite121,  VirtualWrite122,  VirtualWrite123,
    VirtualWrite124,  VirtualWrite125,  VirtualWrite126,  VirtualWrite127,

};

VirtualReadHandler GetVReadHandler(uint8_t pin)
{
    if (pin >= BLYNK_COUNT_OF(VirtualReadHandlerVector))
        return NULL;
//#ifdef VIRTUAL_HAS_PROGMEM
//    return (VirtualReadHandler)pgm_read_word(&VirtualReadHandlerVector[pin]);
//#else
    //Serial.println(pin);
    return VirtualReadHandlerVector[pin];
//#endif
}

VirtualWriteHandler GetVWriteHandler(uint8_t pin)
{
    if (pin >= BLYNK_COUNT_OF(VirtualWriteHandlerVector))
        return NULL;
//#ifdef VIRTUAL_HAS_PROGMEM
//    return (VirtualriteHandler)pgm_read_word(&VirtualWriteHandlerVector[pin]);
//#else
    return VirtualWriteHandlerVector[pin];
//#endif
}
