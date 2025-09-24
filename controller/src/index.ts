import mqtt from "mqtt";
import express from "express";

let client: mqtt.MqttClient = mqtt.connect("mqtt://localhost");

let pos = 0;

client.on("connect", () => {
  console.log("📡 Connected to local MQTT broker 📡");
});

setInterval(() => {
  if (pos == 360) pos = 0;

  const largeAngleRad = pos * (Math.PI / 180); // convert to radians
  const largeValue = Math.sin(largeAngleRad); // grab the sine of the angle, -1 to +1
  const largeDistance = ((largeValue + 1) / 2) * 100; // convert to percentage with 0 being at the 50% mark

  const smallAngleRad = pos * (Math.PI / 180); // convert to radians
  const smallValue = Math.sin(smallAngleRad); // -1 to +1
  const smallDistance = ((smallValue + 1) / 2) * 100; // 0 to 1

  const message = `${largeDistance.toString().padStart(3, "0")},${smallDistance.toString().padStart(3, "0")}`;
  console.log(message);
  client.publish("Diamonds Control", message);
  // console.log(message);
  // await new Promise(r => setTimeout
  pos += 1;
}, 50);

const app: express.Express = express();
const port: number = 3000;

app.use(express.json());

// Enable CORS for all routes
app.use((req, res, next) => {
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Methods", "GET,POST,PUT,DELETE,OPTIONS");
  res.header("Access-Control-Allow-Headers", "Content-Type, Authorization");
  next();
});

app.get("/api/status", (req: express.Request, res: express.Response) => {
  console.log("I am here");
  res.json({ status: "ok", message: "Hello" });
});

app.listen(port, () => {
  console.log(`🚀 Express server running at http://localhost:${port}`);
});
