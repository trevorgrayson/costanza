def should_update(version, **req):
    return present_version() > version


def present_version(**params):
    return 1
