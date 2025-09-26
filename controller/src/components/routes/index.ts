import express, { Request, Response } from "express";
import { MqttClient } from "mqtt";
import Controller from "@/components/animationController";

const app = express();
const port = 3000;

export default (client: MqttClient, controller: Controller) => {
  app.use(express.json());

  // Enable CORS for all routes
  app.use((_, res, next) => {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Methods", "GET,POST,PUT,DELETE,OPTIONS");
    res.header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    next();
  });

  app.post("/api/animation/perlin", (_: Request, res: Response) => {
    controller.perlin();
    res.json({ status: "ok", message: "Perlin Noise Animation" });
  });

  app.post("/api/animation/sine", (_: Request, res: Response) => {
    controller.sine();
    res.json({ status: "ok", message: "Sine Wave Animation" });
  });

  app.post("/api/animation/stop", (_: Request, res: Response) => {
    controller.idle();
    res.json({ status: "ok", message: "Animation Stopped" });
  });

  app.post("/api/status", (_: Request, res: Response) => {
    res.json({ status: "ok", message: "I am alive" });
  });

  app.post("/api/enableMQTT", (_: Request, res: Response) => {
    res.json({ status: "ok", message: "Listening to MQTT messages" });
    client.publish("Diamonds Control", "a 1");
  });

  app.post("/api/home", (_: Request, res: Response) => {
    res.json({ status: "ok", message: "Homing Diamonds" });
    client.publish("Diamonds Control", "a 2");
  });

  app.post("/api/disableSteppers", (_: Request, res: Response) => {
    res.json({ status: "ok", message: "Steppers disabled" });
    client.publish("Diamonds Control", "a 3");
  });

  app.post("/api/resetHome", (_: Request, res: Response) => {
    res.json({ status: "ok", message: "Resetting home position" });
    client.publish("Diamonds Control", "a 4");
  });

  app.listen(port, () => {
    console.log(`🚀 Express server running at http://localhost:${port}`);
  });

  return app;
};
