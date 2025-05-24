# 預處理：計算字串 s 的 LSP 陣列（pi 陣列）
def preprocessor(s: str) -> List[int]:
    n = len(s)
    dp = [0] * n
    for i in range(1, n):
        j = dp[i - 1]
        while j > 0 and s[i] != s[j]:
            j = dp[j - 1]
        if s[i] == s[j]:
            j += 1
        dp[i] = j
    return dp

# KMP 主邏輯：在 t 中匹配 s，回傳每個位置前綴匹配長度（也可以改成匹配位置）
def kmp(s: str, t: str) -> List[int]:
    n = len(s)
    m = len(t)
    lsp = preprocessor(t)  # 注意：這裡 t 是 pattern
    dp = [0] * n
    dp[0] = int(s[0] == t[0])

    for i in range(1, n):
        j = dp[i - 1]
        while j > 0 and s[i] != t[j]:
            j = lsp[j - 1]
        if s[i] == t[j]:
            j += 1
        dp[i] = j
    return dp
