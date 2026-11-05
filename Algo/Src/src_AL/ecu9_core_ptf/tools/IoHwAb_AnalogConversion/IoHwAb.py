from math import log2

#conversion parameters are stored as sint16 [-2^15..2^15-1]
MAX_DYNAMIC = (1 << 15) -1

def compute_params(num, den):
  # num/den = (num*2^n)/(den/2^n) = (num*2^n/den)/2^n
  # (num/den)*2^n < MAX_DYNAMIC -> n=...
  n = int( log2( (MAX_DYNAMIC)/abs(num/den) ) )
  
  new_num = round(num*(1<<n)/den)
  
  return new_num, n

#example from ECU9XLEAN HW, AIN inputs
#Vadc = Vin * 21 / (82,5 + 21) -> Vin @ Vadc=3300mV = 16264mV
points = [
          #ADC Raw, converted value
          [0, 0],
          [4095, 16264],
          #...
         ]

with open("out/config.txt", 'w') as outfile:

  if len(points) > 2:
    outfile.write(f"STATIC CONST(IoHwAb_AnalogLinearizedPointType, IOHWAB_CONST) IoHwAb_ConvParam_LinearizedPoints[{len(points)}] = \n{{\n")
  elif len(points) == 2:
    outfile.write("STATIC CONST(IoHwAb_AnalogLinearConvParamsType, IOHWAB_CONST) IoHwAb_ConvParam_Linear = \n{\n")
  else:
    raise ValueError("error in points")

  print( "original m | ", "new m | ", "error (delta)" )

  for i in range(len(points)-1):
    #find m for the segment
    num = points[i+1][1] - points[i][1]
    den = points[i+1][0] - points[i][0]

    params = compute_params(num, den)

    print( num/den, params[0]/(1<<params[1]), (num/den - params[0]/(1<<params[1])) )

    if len(points) > 2:
      outfile.write(f"  {{\n    /* Raw (x) */\n    {points[i][0]},\n    /* Converted (y) */\n    {points[i][1]},\n    /* SlopeNum */\n    {params[0]},\n    /* SlopeDen */\n    {params[1]},\n  }},\n")
    else:
      outfile.write(f"  /* Offset */\n  {points[i][1]},\n  /* SlopeNum */\n  {params[0]},\n  /* SlopeDen */\n  {params[1]}\n")

  if len(points) > 2:
    outfile.write(f"  {{\n    /* Raw (x) */\n    {points[-1][0]},\n    /* Converted (y) */\n    {points[-1][1]},\n    /* DoNotCare */\n    0xFFFF,\n    /* DoNotCare */\n    0xFF,\n  }},\n}};\n\n")
    outfile.write("STATIC CONST(IoHwAb_AnalogLinearizedConvParamsType, IOHWAB_CONST) IoHwAb_ConvParam_Linearized = \n{\n")
    outfile.write(f"  /* NumOfPoints */\n  {len(points)},\n  /* Points */\n  IoHwAb_ConvParam_LinearizedPoints\n}};")
  else:
    outfile.write("};")
  