export default function applySkew(x: number, min: number, max: number, mid: number) {
    const normalized = (x - min) / (max - min); // 0~1로 정규화
    const skewFactor = Math.log(0.5) / Math.log((mid - min) / (max - min));

    return min + (max - min) * Math.pow(normalized, skewFactor);
}
