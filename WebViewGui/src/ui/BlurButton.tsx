import { Button, type ButtonProps } from '@mantine/core';

interface ExtendedButtonProps
  extends ButtonProps,
    Omit<React.ButtonHTMLAttributes<HTMLButtonElement>, keyof ButtonProps> {}

export default function BlurButton(props: ExtendedButtonProps) {
  const { onMouseDown, onClick, ...rest } = props;

  const handleMouseDown = (e: React.MouseEvent<HTMLButtonElement>) => {
    onMouseDown?.(e);
    e.preventDefault();
  };

  const handleClick = (e: React.MouseEvent<HTMLButtonElement>) => {
    (e.currentTarget as HTMLElement).blur(); // 클릭 후 포커스 제거
    if (onClick) onClick(e);
  };

  return (
    <Button
      {...rest}
      onMouseDown={handleMouseDown}
      onClick={handleClick}
      variant="transparent"
      p={0}
    />
  );
}
