def test_basic_assertion():
    assert 42 == 42

def test_string_match():
    """
    Verifies that the ATROP acronym is correctly derived
    from the protocol's full name.
    """
    name = "Autonomous Topology Optimized Routing Protocol"
    acronym = "".join(word[0] for word in name.split()).lower()
    assert acronym == "atrop"
