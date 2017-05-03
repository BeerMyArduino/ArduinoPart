/*
Arduino -> phone - текстовая строка


нижняя_температура $
верхняя_температура $ 
время_с_начала_варки_на_нужной_температуре $ 
необходимая_температура $ 
необходимое_время_варки $ 
включен_ли_ТЭН (0/1) $
включен_ли_насос

*/



/*
* java code example
* 
*/

class AAP {

	private final String TURN_OFF_HEATING = "h-";
	private final String TURN_ON_HEATING = "h+";
	

	public int bottomTemp = 0;
	public int topTemp = 0;
	public int boilTime = -1;
	public int requiredTemp = 0;
	public int requiredBoilTime = 0;
	public boolean heatingElementOn = false;
	public bookean shakerOn = false;

	public void parse(String s) throws Exception {
		
		String[] parsed = s.split("$");
		
		if (parsed.length != 7) {
			throw new Exception("not parsed message");
		}

		try {
			bottomTemp = Integer.parseInt(parsed[0]);
			topTemp = Integer.parseInt(parsed[1]);
			boilTime = Integer.parseInt(parsed[2]);
			requiredTemp = Integer.parseInt(parsed[3]);
			boilTimeRequired = Integer.parseInt(parsed[4]);
			heatingElementOn = parsed[5] == "1";
			shakerOn = parsed[6] == "1";
		} catch (Exception e) {
			throw new Exception("not parsed message");	
		}
		
	}

	public String turnOffHeatingEl() {
		return TURN_OFF_HEATING;
	}

	public String turnOnHeatingEl() {
		return TURN_ON_HEATING;
	}

	// TODO rest other command functions
}

/*
Phone -> Arduino - массив байт

Тэн вкл/выкл
"h+   "
"h-   "

Насос вкл/выкл
"p+   "
"p-   "


Задать температуру и время и стартануть
"c%t%"
2-й байт - время в минутах
4-й байт - температура


"c%  "



"t%  "
*/