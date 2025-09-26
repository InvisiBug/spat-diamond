import { MqttClient } from "mqtt/*";
import PerlinNoise from "./components/perlinNoise";
import SineWave from "./components/sineWave";

export default class {
  perlinNoise: PerlinNoise;
  sineWave: SineWave;
  client: MqttClient;
  state: string;
  update: boolean;

  constructor(client: MqttClient) {
    this.state = "idle";
    this.update = false;

    this.perlinNoise = new PerlinNoise();
    this.sineWave = new SineWave();
    this.client = client;
  }

  tick() {
    switch (this.state) {
      case "perlin":
        if (!this.update) console.log("Running Perlin Noise Animation");

        const sin = this.perlinNoise.getNoiseValues(true);
        this.client.publish("Diamonds Control", sin);
        break;

      case "sine":
        if (!this.update) console.log("Running Sine Wave Animation");

        const sine = this.sineWave.getValues(true);
        this.client.publish("Diamonds Control", sine);
        break;

      case "idle":
        if (!this.update) console.log("Controller Idle");
        break;

      default:
        break;
    }

    this.update = true;
  }

  public perlin() {
    this.state = "perlin";
    this.update = false;
  }

  public sine() {
    this.state = "sine";
    this.update = false;
  }

  public idle() {
    this.state = "idle";
    this.update = false;
  }
}
