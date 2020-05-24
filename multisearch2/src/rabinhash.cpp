/*
 * rabinhash.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: michael
 */

#include "rabinhash.h"

namespace rabin {

RabinHash::RabinHash() :
		fingerprint(0) {
}

//now inlined
//uint_fast64_t RabinHash::push(uint8_t * value){
//	int j = this->fingerprint >> RabinHash::shift;
//	uint_fast64_t val =  uint_fast64_t (*value);
//	this->fingerprint = ((this->fingerprint << 8) | val) ^ RabinHash::pushTable[j];
//	return this->fingerprint;
//}

uint_fast64_t RabinHash::push(uint8_t * value, uint_fast32_t amount) {
	for (uint_fast32_t i = 0; i < amount; i++) {
		this->push(value + i);
	}
	return this->fingerprint;
}

//shift = degree - 8 = 12 - 8 = 4
//changes together with the pushtable
const uint_fast8_t RabinHash::shift = 4;

//pushtable for X^12 + X^4 + X^2 + X^1 + 1
//remeber to change shift at the same time
const uint_fast64_t RabinHash::pushTable[512] = { 0ul, 4119ul, 8238ul, 12345ul,
		16476ul, 20555ul, 24690ul, 28773ul, 32952ul, 37039ul, 41110ul, 45185ul,
		49380ul, 53491ul, 57546ul, 61661ul, 65904ul, 69991ul, 74078ul, 78153ul,
		82220ul, 86331ul, 90370ul, 94485ul, 98760ul, 102879ul, 106982ul,
		111089ul, 115092ul, 119171ul, 123322ul, 127405ul, 131808ul, 135927ul,
		139982ul, 144089ul, 148156ul, 152235ul, 156306ul, 160389ul, 164440ul,
		168527ul, 172662ul, 176737ul, 180740ul, 184851ul, 188970ul, 193085ul,
		197520ul, 201607ul, 205758ul, 209833ul, 213964ul, 218075ul, 222178ul,
		226293ul, 230184ul, 234303ul, 238342ul, 242449ul, 246644ul, 250723ul,
		254810ul, 258893ul, 263616ul, 267735ul, 271854ul, 275961ul, 279964ul,
		284043ul, 288178ul, 292261ul, 296312ul, 300399ul, 304470ul, 308545ul,
		312612ul, 316723ul, 320778ul, 324893ul, 328880ul, 332967ul, 337054ul,
		341129ul, 345324ul, 349435ul, 353474ul, 357589ul, 361480ul, 365599ul,
		369702ul, 373809ul, 377940ul, 382019ul, 386170ul, 390253ul, 395040ul,
		399159ul, 403214ul, 407321ul, 411516ul, 415595ul, 419666ul, 423749ul,
		427928ul, 432015ul, 436150ul, 440225ul, 444356ul, 448467ul, 452586ul,
		456701ul, 460368ul, 464455ul, 468606ul, 472681ul, 476684ul, 480795ul,
		484898ul, 489013ul, 493288ul, 497407ul, 501446ul, 505553ul, 509620ul,
		513699ul, 517786ul, 521869ul, 527232ul, 531351ul, 535470ul, 539577ul,
		543708ul, 547787ul, 551922ul, 556005ul, 559928ul, 564015ul, 568086ul,
		572161ul, 576356ul, 580467ul, 584522ul, 588637ul, 592624ul, 596711ul,
		600798ul, 604873ul, 608940ul, 613051ul, 617090ul, 621205ul, 625224ul,
		629343ul, 633446ul, 637553ul, 641556ul, 645635ul, 649786ul, 653869ul,
		657760ul, 661879ul, 665934ul, 670041ul, 674108ul, 678187ul, 682258ul,
		686341ul, 690648ul, 694735ul, 698870ul, 702945ul, 706948ul, 711059ul,
		715178ul, 719293ul, 722960ul, 727047ul, 731198ul, 735273ul, 739404ul,
		743515ul, 747618ul, 751733ul, 755880ul, 759999ul, 764038ul, 768145ul,
		772340ul, 776419ul, 780506ul, 784589ul, 790080ul, 794199ul, 798318ul,
		802425ul, 806428ul, 810507ul, 814642ul, 818725ul, 823032ul, 827119ul,
		831190ul, 835265ul, 839332ul, 843443ul, 847498ul, 851613ul, 855856ul,
		859943ul, 864030ul, 868105ul, 872300ul, 876411ul, 880450ul, 884565ul,
		888712ul, 892831ul, 896934ul, 901041ul, 905172ul, 909251ul, 913402ul,
		917485ul, 920736ul, 924855ul, 928910ul, 933017ul, 937212ul, 941291ul,
		945362ul, 949445ul, 953368ul, 957455ul, 961590ul, 965665ul, 969796ul,
		973907ul, 978026ul, 982141ul, 986576ul, 990663ul, 994814ul, 998889ul,
		1002892ul, 1007003ul, 1011106ul, 1015221ul, 1019240ul, 1023359ul,
		1027398ul, 1031505ul, 1035572ul, 1039651ul, 1043738ul, 1047821ul,
		1050391ul, 1054464ul, 1058617ul, 1062702ul, 1066827ul, 1070940ul,
		1075045ul, 1079154ul, 1083311ul, 1087416ul, 1091457ul, 1095574ul,
		1099763ul, 1103844ul, 1107933ul, 1112010ul, 1115751ul, 1119856ul,
		1123913ul, 1128030ul, 1132091ul, 1136172ul, 1140245ul, 1144322ul,
		1148639ul, 1152712ul, 1156849ul, 1160934ul, 1164931ul, 1169044ul,
		1173165ul, 1177274ul, 1181175ul, 1185248ul, 1189337ul, 1193422ul,
		1197483ul, 1201596ul, 1205637ul, 1209746ul, 1213775ul, 1217880ul,
		1221985ul, 1226102ul, 1230099ul, 1234180ul, 1238333ul, 1242410ul,
		1246343ul, 1250448ul, 1254569ul, 1258686ul, 1262811ul, 1266892ul,
		1271029ul, 1275106ul, 1279039ul, 1283112ul, 1287185ul, 1291270ul,
		1295459ul, 1299572ul, 1303629ul, 1307738ul, 1311447ul, 1315520ul,
		1319673ul, 1323758ul, 1327755ul, 1331868ul, 1335973ul, 1340082ul,
		1344111ul, 1348216ul, 1352257ul, 1356374ul, 1360435ul, 1364516ul,
		1368605ul, 1372682ul, 1377191ul, 1381296ul, 1385353ul, 1389470ul,
		1393659ul, 1397740ul, 1401813ul, 1405890ul, 1409823ul, 1413896ul,
		1418033ul, 1422118ul, 1426243ul, 1430356ul, 1434477ul, 1438586ul,
		1441847ul, 1445920ul, 1450009ul, 1454094ul, 1458283ul, 1462396ul,
		1466437ul, 1470546ul, 1474703ul, 1478808ul, 1482913ul, 1487030ul,
		1491155ul, 1495236ul, 1499389ul, 1503466ul, 1507655ul, 1511760ul,
		1515881ul, 1519998ul, 1523995ul, 1528076ul, 1532213ul, 1536290ul,
		1540607ul, 1544680ul, 1548753ul, 1552838ul, 1556899ul, 1561012ul,
		1565069ul, 1569178ul, 1576087ul, 1580160ul, 1584313ul, 1588398ul,
		1592523ul, 1596636ul, 1600741ul, 1604850ul, 1608751ul, 1612856ul,
		1616897ul, 1621014ul, 1625203ul, 1629284ul, 1633373ul, 1637450ul,
		1641959ul, 1646064ul, 1650121ul, 1654238ul, 1658299ul, 1662380ul,
		1666453ul, 1670530ul, 1674591ul, 1678664ul, 1682801ul, 1686886ul,
		1690883ul, 1694996ul, 1699117ul, 1703226ul, 1707639ul, 1711712ul,
		1715801ul, 1719886ul, 1723947ul, 1728060ul, 1732101ul, 1736210ul,
		1740495ul, 1744600ul, 1748705ul, 1752822ul, 1756819ul, 1760900ul,
		1765053ul, 1769130ul, 1773319ul, 1777424ul, 1781545ul, 1785662ul,
		1789787ul, 1793868ul, 1798005ul, 1802082ul, 1806271ul, 1810344ul,
		1814417ul, 1818502ul, 1822691ul, 1826804ul, 1830861ul, 1834970ul,
		1837399ul, 1841472ul, 1845625ul, 1849710ul, 1853707ul, 1857820ul,
		1861925ul, 1866034ul, 1870319ul, 1874424ul, 1878465ul, 1882582ul,
		1886643ul, 1890724ul, 1894813ul, 1898890ul, 1902631ul, 1906736ul,
		1910793ul, 1914910ul, 1919099ul, 1923180ul, 1927253ul, 1931330ul,
		1935519ul, 1939592ul, 1943729ul, 1947814ul, 1951939ul, 1956052ul,
		1960173ul, 1964282ul, 1969079ul, 1973152ul, 1977241ul, 1981326ul,
		1985515ul, 1989628ul, 1993669ul, 1997778ul, 2001679ul, 2005784ul,
		2009889ul, 2014006ul, 2018131ul, 2022212ul, 2026365ul, 2030442ul,
		2034375ul, 2038480ul, 2042601ul, 2046718ul, 2050715ul, 2054796ul,
		2058933ul, 2063010ul, 2067071ul, 2071144ul, 2075217ul, 2079302ul,
		2083363ul, 2087476ul, 2091533ul, 2095642ul };

}