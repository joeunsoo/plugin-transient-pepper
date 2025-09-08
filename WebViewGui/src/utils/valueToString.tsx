export interface ValueToString {
  (value: number, subDigit?: number): string
}

export function msToString(value: number, subDigit?: number) {
  return `${(value*1000).toFixed(subDigit || 0)} ms`;
}

export function percentToString(value: number) {
  return `${value} %`;
}

export function dBToString(value: number) {
  return `${value} dB`;
}
