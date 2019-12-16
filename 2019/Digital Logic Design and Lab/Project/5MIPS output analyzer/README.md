# 5-instruction MIPS output analyzer

5개의 instruction에 대한 MIPS assembly code를 분석하여 output과 hex-encoded memory-assignment verilog code를 출력해 주는 스크립트입니다. 

구현된 instruction은 다음과 같습니다. 

1. ADD
2. ADI
3. LHI
4. JMP
5. WWD (custom)

!!!!! 반드시 형식을 지켜 주세요. 함께 제공되는 testcode.v와 testcode.txt를 참조해 주세요. 

작성자의 테스트 목적으로 제작되었기 때문에, 오류로 인한 보상은 하지 않습니다. 참고용으로만 사용 부탁드립니다.


[사용법] py 파일과 input 파일을 같은 경로에 두고, 해당 경로에서
(Windows) CMD를 열고
(Linux) 터미널에서

```bash
python project_get_output.py
```

를 실행하면 output file로 out_code.v, output_result.txt가 나옵니다. 
