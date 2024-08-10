# RFID-lock-System_with-arduino 
<p></p>
<ul>
<li><h2>components : </h2></li>
<ul>
    <li>arduino nano</li>
    <li>RFID module</li>
    <li>Keypad</li>
    <liServo motor</li>
    <li>Buzzer</li>
    <li>LCD screen</li>
    <li>I2C module</li>
    <li>Battery 9v</li>
</ul>
        <hr/>
<li><h2>how does it work : </h2></li>
<p>
 <ul>
     <li>
    The system operates seamlessly: the user initiates the process by scanning their tag with the RFID module, acting as the RFID reader. If the tag matches an entry in the Arduino's database, representing the computer system, the door grants access. However, should an incorrect tag be scanned, a message promptly appears on the LCD screen, notifying the user of the discrepancy.
</li>
    <p></p>
<li>
To bolster security, an additional feature has been integrated into the system. This feature allows users three attempts to scan their tag incorrectly. After the third unsuccessful attempt, an alarm is triggered, signaling an unauthorized access attempt. This alarm persists for a predetermined duration, serving as a warning that someone without proper authorization has attempted entry. During this period, the system temporarily suspends tag scanning and instead prompts the user to enter a preset password. Only upon successful entry of this password does the door grant access. This multifaceted mechanism provides a significantly higher level of security compared to traditional mechanical locking systems.
 </li>
</ul>
</p>
</ul>
 <ul>
     <hr/>
       <li><h2>Final form : </h2></li> 
     <p>vedio link : https://youtu.be/3Nf48kX4Zkw?si=AvTFv-3GKPlzDj7f </p>
 </ul>
  
    
       
   

