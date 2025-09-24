import mqtt from "mqtt";

let client: mqtt.MqttClient = mqtt.connect("mqtt://localhost");

let pos = 0;

client.on("connect", () => {
  console.log("📡 Connected to local MQTT broker 📡");
});

setInterval(() => {
  client.publish("Diamonds Control", "000,000");
  if (pos == 360) pos = 0;

  const largeAngleRad = (pos * 1000) / 57296; // convert to radians
  const largeValue = Math.sin(largeAngleRad); // grab the sine of the angle, -1 to +1
  const largeDistance = Math.floor(((largeValue + 1) / 2) * 100); // convert to percentage with 0 being at the 50% mark

  const smallAngleRad = (pos * 1000) / 57296; // convert to radians
  const smallValue = Math.sin(smallAngleRad); // -1 to +1
  const smallDistance = Math.floor(((smallValue + 1) / 2) * 100); // 0 to 1

  const message = `${largeDistance.toString().padStart(3, "0")},${smallDistance.toString().padStart(3, "0")}`;
  console.log(message);
  client.publish("Diamonds Control", message);
  // console.log(message);
  // await new Promise(r => setTimeout
  pos += 1;

  // const largeAngleDeg = millis() / 100;                // angle in degrees over time
  //       const largeAngleRad = largeAngleDeg * 1000 / 57296;  // convert to radians
  //       const largeValue = sin(largeAngleRad);               // grab the sine of the angle, -1 to +1
  //       const largeDistance = (largeValue + 1) / 2 * 100;    // convert to percentage with 0 being at the 50% mark
  //       large.goToPercentage(largeDistance);                 // move the large diamond

  //       // Serial << "Large angle deg: " << largeAngleDeg << "\t Large: " << largeDistance << endl;

  //       const smallAngle = 180 + millis() / 100.0;         // time in seconds angle
  //       const smallAngleRad = smallAngle * 1000 / 57296;   // convert to radians
  //       const smallValue = sin(smallAngleRad);             // -1 to +1
  //       const smallDistance = (smallValue + 1) / 2 * 100;  // 0 to 1

  //       small.goToPercentage(smallDistance);
  // // let colours = [];
  // // for (let i = 0; i < 3; i++) {
  // //   const colour = availableColours[Math.floor(Math.random() * availableColours.length)];
  // //   colours.push([hexToRgb(colour)[0], hexToRgb(colour)[1], hexToRgb(colour)[2]]);
  // // }
  // // colours[2] = [255, 0, 0];
  // // client.publish("Uplight Control", JSON.stringify(colours));
  // // console.log(colours);
  // // console.log("Uplights updated");
}, 75);
