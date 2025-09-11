export default function fromNormalized(normalized: number, min: number, max: number, mid: number) {
    const skewFactor = Math.log(0.5) / Math.log((mid - min) / (max - min));

    return min + (max - min) * Math.pow(normalized, skewFactor);
}
