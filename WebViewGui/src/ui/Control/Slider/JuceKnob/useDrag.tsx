import { useCallback, useRef, useState } from 'react';
import { MotionValue } from 'framer-motion';

interface UseDragProps {
  handleValue: MotionValue<number>;
  progressScaleValue: MotionValue<number>;
  dragRange: number;
  shiftSensitivity?: number;
  onDragStart?: () => void;
  onChangeCommitted?: (e: Event, value: number) => void;
  setIsDragParent?: React.Dispatch<React.SetStateAction<boolean>>;
}

export function useDrag({
  handleValue,
  progressScaleValue,
  dragRange,
  shiftSensitivity = 1,
  onDragStart,
  onChangeCommitted,
  setIsDragParent,
}: UseDragProps) {
  const lastYRef = useRef(0);
  const [isDrag, setIsDrag] = useState(false);

  const onMouseDown = useCallback(
    (e: React.MouseEvent) => {
      if (e.button !== 0) return;

      setIsDrag(true);
      setIsDragParent?.(true);
      onDragStart?.();

      lastYRef.current = e.clientY;

      const onMouseMove = (ev: MouseEvent) => {
        const dy = ev.clientY - lastYRef.current;
        const sensitivity = ev.shiftKey ? shiftSensitivity : 1;
        const newValue = Math.max(-dragRange, Math.min(0, handleValue.get() + dy * sensitivity));
        handleValue.set(newValue);
        lastYRef.current = ev.clientY;
      };

      const onMouseUp = () => {
        onChangeCommitted?.(new Event('change'), progressScaleValue.get());
        setIsDrag(false);
        setIsDragParent?.(false);

        window.removeEventListener('mousemove', onMouseMove);
        window.removeEventListener('mouseup', onMouseUp);
      };

      window.addEventListener('mousemove', onMouseMove);
      window.addEventListener('mouseup', onMouseUp);
    },
    [
      setIsDragParent,
      onDragStart,
      shiftSensitivity,
      dragRange,
      handleValue,
      onChangeCommitted,
      progressScaleValue,
    ]
  );

  return { isDrag, onMouseDown };
}
