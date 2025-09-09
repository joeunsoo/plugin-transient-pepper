import { create } from 'zustand';

interface SnackbarState {
  open: boolean; // 열기 여부
  message: string;
  setOpen: (message: string) => void; // 열기 여부 설정
  onClose: () => void; // 닫기
}

export const useSnackbarStore = create<SnackbarState>((set) => ({
  open: false,
  message: '',
  setOpen: (message: string) => set(() => ({
    open: true,
    message,
  })),
  onClose: () => set(() => ({ open: false })),
}));
