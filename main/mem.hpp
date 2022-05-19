#ifndef MEM_H
#define MEM_H

const char str1[] PROGMEM = " ЗА\n  ЛЮБОВЬ";
const char str2[] PROGMEM = " ЧТОБЫ\n  ВСЕ";
const char str3[] PROGMEM = " ЗА ВСЁ\n  ХОРОШЕЕ";
const char str4[] PROGMEM = " ЗА\n  ЗДОРОВЬЕ";
const char str5[] PROGMEM = " ЗА\n  ДЕТЕЙ";
const char str6[] PROGMEM = "ЗА\nРОДИТЕЛЕЙ";
const char str7[] PROGMEM = " ЗА\n  ДРУЖБУ";
const char str8[] PROGMEM = " БЫТЬ\n  ДОБРУ";
const char str9[] PROGMEM = "  ЗА МИР";
const char str10[] PROGMEM = " НЕ\n  ЧОКАЯСЬ";
const char str11[] PROGMEM = " ЗА\n  ЖИЗНЬ";
const char str12[] PROGMEM = "  ЗА ДАМ";
const char str13[] PROGMEM = " ЗА\n  РОССИЮ";
const char str14[] PROGMEM = " ЗА\n  МУЖЧИН";
const char str15[] PROGMEM = " ЗА\n  УДАЧУ";
const char str16[] PROGMEM = "  ЗА НАС";
const char str17[] PROGMEM = " ЗА\n  КРАСОТУ";
const char str18[] PROGMEM = " ЗА\n  ДОБРОТУ";
const char str19[] PROGMEM = " ЗА\n  ПОГОДУ";
const char str20[] PROGMEM = " ЗА\n  ПРИРОДУ";
const char str21[] PROGMEM = " ЗА\n  ХОЗЯИНА";
const char str22[] PROGMEM = " ЗА\n  БУДУЩЕЕ";
const char str23[] PROGMEM = " ЗА\n  ПАМЯТЬ";
const char str24[] PROGMEM = " ЗА\n  ОТДЫХ";
const char str25[] PROGMEM = "ЗА\nНАСТРОЕНИЕ";
const char str26[] PROGMEM = " ЧТОБ\n  СТОЯЛ";
const char str27[] PROGMEM = " ЗА\n  ДОСТАТОК";
const char str28[] PROGMEM = " ЗА\n  КОСМОС";
const char str29[] PROGMEM = " ЗА\n  ТЕРПЕНИЕ";
const char str30[] PROGMEM = " ЗА\n  МЕДВЕДЕЙ";
const char str31[] PROGMEM = " ЗА\n  ЛОГИКУ";
const char str32[] PROGMEM = "ЗА\n ТРЕЗВОСТЬ";
const char str33[] PROGMEM = " ЗА\n  УСПЕХ";
const char str34[] PROGMEM = " ЗА\n  ПОБЕДУ";

const char* const names[] PROGMEM = {
  str1,   str2,   str3,   str4,   str5,
  str6,   str7,   str8,   str9,   str10,
  str11,  str12,  str13,  str14,  str15,
  str16,  str17,  str18,  str19,  str20,
  str21,  str22,  str23,  str24,  str25,
  str26,  str27,  str28,  str29,  str30,
  str31,  str32,  str33,  str34
};

String printPGM(byte idx) {
  PGM_P p = pgm_read_word(names + idx);
  char buf[strlen_P(p)];
  strcpy_P(buf, p);
  return String(buf);
}

#endif
