import pkg from "noisejs";
// @ts-ignore
const { Noise } = pkg;
import { mapRange } from "@/components/utils";

export default class {
  private noise: any;
  private pos: number;

  constructor() {
    this.noise = new Noise(Math.random());
    this.pos = 0;
  }

  public getNoiseValues(log: boolean): string {
    const smallNoise = this.noise.perlin2(this.pos / 100, this.pos / 100);
    const offset = 0.1;
    const largeNoise = this.noise.perlin2(offset + this.pos / 100, offset + this.pos / 100);

    this.pos += 1;

    const smallDiamond = mapRange(smallNoise, -1, 1, 0, 100).toFixed(0).toString().padStart(2, "0");

    const largeDiamond = mapRange(largeNoise, -1, 1, 0, 100).toFixed(0).toString().padStart(2, "0");

    if (log) console.log(`Perlin Noise: ${smallDiamond},${largeDiamond}`);

    return `${smallDiamond},${largeDiamond}`;
  }
}
