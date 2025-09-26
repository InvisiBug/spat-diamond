import mqtt from "mqtt";
import startRoutes from "@/components/routes";
import Controller from "@/components/animationController";

const client = mqtt.connect("mqtt://localhost");
const controller = new Controller(client);

client.on("connect", () => {
  console.log("📡 Connected to local MQTT broker 📡");
});

startRoutes(client, controller);

setInterval(() => {
  controller.tick();
}, 50);
