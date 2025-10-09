# FinalProjectCompro

#USER/Password/Role
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

# Compile and run
//compile code//  
gcc -o unit_test.exe unit_test.c
gcc -o Final_Project_CECS.exe Final_Project_CECS.c
gcc -o E2E.exe E2E.c
//run//  
.\unit_test.exe
.\Final_Project_CECS.exe
.\E2E.exe
