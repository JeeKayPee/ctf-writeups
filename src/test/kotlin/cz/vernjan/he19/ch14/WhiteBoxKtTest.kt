package cz.vernjan.he19.ch14

import org.apache.commons.codec.binary.Hex
import org.junit.Test

import org.junit.Assert.*

class WhiteBoxKtTest {

    @Test
    fun swapRowsWithColumns() {
        val state = "0123456789abcdef".toByteArray()

        swapRowsWithColumns(state)

        assertEquals("048c159d26ae37bf", String(state))
    }

    @Test
    fun undoSwapRowsWithColumns() {
        val state = "048c159d26ae37bf".toByteArray()

        swapRowsWithColumns(state)

        assertEquals("0123456789abcdef", String(state))
    }

    @Test
    fun shiftRows() {
        val state = "0123456789abcdef".toByteArray()

        shiftRows(state)

        assertEquals("01235674ab89fcde", String(state))
    }

    @Test
    fun lastEncryptionRound() {
        val state = "0123456789abcdef".toByteArray()

        lastEncryptionRound(state)

        assertArrayEquals(
            byteArrayOf(-49, 124, -52, -27, -71, 20, 120, -120, -71, -126, -10, -96, -32, 97, 33, -27), state)
    }

    @Test
    fun encryptBlock1() {
        val text = "One nice block!!"

        val encrypted = encryptBlock(text.toByteArray())

        assertEquals("de20759da69aef1a0d2f309a37ac334b", Hex.encodeHexString(encrypted))
    }

    @Test
    fun encryptBlock2() {
        val text = "abcdefghijklmnop"

        val encrypted = encryptBlock(text.toByteArray())

        assertEquals("7ec041d65b2ff88c35b8626d8c2208d2", Hex.encodeHexString(encrypted))
    }

    @Test
    fun decrypt() {
        val text = "9771a6a9aea773a93edc1b9e82b74503"

        val decrypted = encryptBlock(Hex.decodeHex(text))

        println(String(decrypted))
    }


}