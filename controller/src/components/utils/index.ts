export const mapRange = (
  value: number,
  inMin: number,
  inMax: number,
  outMin: number,
  outMax: number,
): number => {
  return ((value - inMin) / (inMax - inMin)) * (outMax - outMin) + outMin;
};
