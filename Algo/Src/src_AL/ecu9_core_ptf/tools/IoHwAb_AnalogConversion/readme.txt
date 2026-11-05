Script to help the configuration of conversion function

To use it configure the conversion table as needed:
  for a linear conversion (i.e. analog input with partition) just configure two points, the minimum (0V in, 0V ADC) and the maximum (max V in - to be computed, VCC volt ADC - saturation).
  for a linearized function, just put all the points in format [raw adc, converted value]. An example can be an NTC table provided by HW team

Then just run the batch file. In out/config.txt the script generates the data structures to be put in IoHwAb_AnalogCfg.c. Just change the structures name.
The output will show, for every segment, the original m, the new aproximated m and the delta between them.