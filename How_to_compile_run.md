# FinalProjectCompro

#USER/Password/Role
```shell
{"admin", "1234", "Admin"},
{"staff", "1234", "Staff"},
{"user", "1234", "General"}
ต้องกรอก รหัส ก่อนเข้าใช้งานเพื่อสิทธ์ Role ของสิทธ์การเข้าถึงในการเข้าถึง เพิ่ม ค้นหา เเก้ไข ลบ ของใบอนุญาตตามสิทธินั้นๆ
โดย Admin = เพิ่ม/แก้ไข/ลบ/ดูข้อมูล Staff = เพิ่มและดูข้อมูล General = ดูข้อมูลบางส่วน
เมื่อเปิดโปรแกรม คุณจะเห็นข้อความ:
ให้เลือกภาษาก่อน (th/en): th
กรอกรหัส Role ที่ให้ไว้ ชื่อผู้ใช้: admin เเละ รหัส
เข้าสู่ระบบสำเร็จ (Role: Admin)
จากนั้นจะเเสดงเมนู
```

# Compile and run
##compile code
```shell
gcc -o unit_test.exe unit_test.c
gcc -o Final_Project_CECS.exe Final_Project_CECS.c
gcc -o E2E.exe E2E.c
```

##run
```shell
.\unit_test.exe
.\Final_Project_CECS.exe
.\E2E.exe
```
##อีกเเบบ
```shell
หากโหลดเเล้ว compile ตามไม่ได้ให้ลองตรวจสอบก่อนว่าเข้าถึง path ที่ไฟล์อยุ่เเล้วยัง โดยให้

ทำใน terminal vs code

cd /d "ที่อยุ่ของไฟล์"

ex. cd /d "E:\Final_Project_CECS\code"

//compile code// Windows

gcc -std=c11 -Wall -Wextra -O2 Final_Project_CECS.c unit_test.c E2E.c -o License_management.exe

macOS / Linux//

gcc -std=c11 -Wall -Wextra -O2 Final_Project_CECS.c unit_test.c E2E.c -o License_management

//run//
License_management.exe (window)

./License_management (mac/linux)
```


